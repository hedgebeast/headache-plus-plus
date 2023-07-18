#ifndef QF633_CODE_VOLSURFBUILDER_H
#define QF633_CODE_VOLSURFBUILDER_H

#include <map>
#include "Msg.h"
#include "Date.h"
#include "CubicSmile.h"
#include <tuple>


/* VolSurfBuilder keeps track of the latest snapshot of the option market 
 * using the member variable std::map<std::string, TickData> currentSurfaceRaw 
 * - the latest tick data of all option contracts in the market.
 */ 

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& volSurf) {
    for (const auto& pair : volSurf) 
        os << pair.second << std::endl;
    return os;
}

template <typename V>
std::ostream& operator<<(std::ostream& os, const std::map<datetime_t, V>& volSurf) {
    for (const auto& pair : volSurf) {
        if (pair.first == datetime_t{2023,3,31}){
            size_t counter {0};
            for (const auto & i : pair.second){
//                std::cout << counter << std::endl;
                os << i << std::endl;
                counter++;
            }
            std::cout << "The number of contracts with this expiry: " << counter << std::endl;
        }
    }
    return os;
}

template<class Smile>
class VolSurfBuilder {
public:
    void Process(const Msg& msg);  //process message
    void PrintInfo();
    std::map<datetime_t, std::pair<Smile, double>> FitSmiles();
    
protected:
    // we want to keep the best level information for all instruments
    // here we use a map from contract name to BestLevelInfo, the key is contract name
    std::map<std::string, TickData> currentSurfaceRaw {};
    
//enum Month{JAN=1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};
std::map<std::string, int> monthMap =  {
                                        { "JAN", 1 },
                                        { "FEB", 2 },
                                        { "MAR", 3 },
                                        { "APR", 4 },
                                        { "MAY", 5 },
                                        { "JUN", 6 },
                                        { "JUL", 7 },
                                        { "AUG", 8 },
                                        { "SEP", 9 },
                                        { "OCT", 10 },
                                        { "NOV", 11 },
                                        { "DEC", 12 }
                                        };
};

/* Step 2: Maintain the latest market snapshot
 * 
 * Every time VolSurfBuilder takes a Msg, it checks if it is a snapshot or an update. 
 * If the message is a snapshot, it will discard the previously maintained market, to avoid error accumulation. 
 * If the message is an update, it will just apply the updates to the currently maintained market snapshot.
 * 
 * Recall that std::vector<TickData> Updates;
 */ 
 
template <class Smile>
void VolSurfBuilder<Smile>::Process(const Msg& msg) {
    // TODO (Step 2)
    if (msg.isSnap) {
        std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Latest Market SNAPSHOT ALERT >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << std::endl;
        // DISCARD currently maintained market snapshot, and construct a new copy based on the input Msg
        currentSurfaceRaw.clear();

        for (auto itr = msg.Updates.begin(); itr != msg.Updates.end(); itr++) {
            currentSurfaceRaw.insert({(*itr).ContractName, *itr});
        }
        
//        PrintInfo();
    } 
    
    else {
        // UPDATE the currently maintained market snapshot
        for (auto itr = msg.Updates.begin(); itr != msg.Updates.end(); itr++){
//            std::cout << "Updates for contract: " << (*itr).ContractName << std::endl;
            
            if (currentSurfaceRaw.find((*itr).ContractName) != currentSurfaceRaw.end()){
                currentSurfaceRaw[(*itr).ContractName] = *itr;
//                std::cout << "contract name: "<< (*itr).ContractName << std::endl;
            }
            else{
                currentSurfaceRaw.insert({(*itr).ContractName, *itr});
//                std::cout << "contract name: "<< (*itr).ContractName << std::endl;
            }
        }
        
//        PrintInfo();
    }
}


template <class Smile>
void VolSurfBuilder<Smile>::PrintInfo() {   //print out the information of the market snapshot at the given interval

    // TODO (Step 2): you may print out information about VolSurfBuilder's currentSnapshot to test
    std::cout << "\n<<<<<<<<<<<<<<<<<<<<<< CURRENT SNAPSHOT >>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    std::cout << currentSurfaceRaw << std::endl;
}


/* Step 3: Fit smile at regular time interval, and stream the marks and fitting error to output files
 * (We want to fit our own volatility smile models (cubic spline) to the raw market data so it is easier for pricing and signal research)
 * 
 * Recall that contractName: Underlying_(ExpiryDate)_(Strike)_OptionType
 * Recall that std::map<std::string, TickData> currentSurfaceRaw;
 */ 

template <class Smile>
std::map<datetime_t, std::pair<Smile, double>> VolSurfBuilder<Smile>::FitSmiles() {
    
    std::map<datetime_t, std::vector<TickData>> tickersByExpiry{};
    std::string dateSubstring {};
    int y,m,d;
    
    // TODO (Step 3): group the tickers in the current market snapshot by expiry date (DDMMMYY format), and construct tickersByExpiry
//    PrintInfo();
    
    //Group by expiry date first
    for (auto iter = currentSurfaceRaw.begin(); iter != currentSurfaceRaw.end(); iter++){
        
        // Find the position of the underscore delimiter    (e.g. BTC-30SEP22-60000-P)
        size_t delimiterPos = ((*iter).first).find('-');

        // Check if the delimiter is found and there are characters after it
        if (delimiterPos != std::string::npos && delimiterPos + 1 < ((*iter).first).length()) {
            // Extract the substring after the delimiter
            dateSubstring = ((*iter).first).substr(delimiterPos + 1);

            // Find the position of the next underscore delimiter if present
            size_t nextDelimiterPos = dateSubstring.find('-');

            // If the next delimiter is found, extract the substring before it
            if (nextDelimiterPos != std::string::npos) {
                dateSubstring = dateSubstring.substr(0, nextDelimiterPos);
            }
//        std::cout << dateSubstring << std::endl;        //e.g. '24JUN22'
//        std::cout << dateSubstring.substr(2,3) << std::endl;

        if (dateSubstring.length()==7){
            d = std::stoi(dateSubstring.substr(0,2));
            m = monthMap[dateSubstring.substr(2,3)];
            y = std::stoi("20" + dateSubstring.substr(5,2));
        }
        
        else{
            d = std::stoi(dateSubstring.substr(0,1));
            m =  monthMap[dateSubstring.substr(1,3)];
            y = std::stoi("20" + dateSubstring.substr(4,2));
        }
        
        datetime_t expiryDate{y,m,d};
//        std::cout << expiryDate << std::endl;   //2022 6 24
        std::vector<TickData> tickDataVector {};
        
        if (tickersByExpiry.find(expiryDate) != tickersByExpiry.end()){
//            std::cout << "START" << std::endl;
//            std::cout << expiryDate << std::endl;
//            std::cout << tickersByExpiry << std::endl;
            tickDataVector = tickersByExpiry[expiryDate];
            tickDataVector.push_back((*iter).second);
            tickersByExpiry.erase(expiryDate);
            tickersByExpiry.insert({expiryDate, tickDataVector});
//            std::cout << "END" << std::endl;
//            std::cout << tickersByExpiry << std::endl;
        }
        else{
//            std::cout << "BEGINNING" << std::endl;
//            std::cout << expiryDate << std::endl;
            tickDataVector.push_back((*iter).second);
            tickersByExpiry.insert({expiryDate, tickDataVector});
//            std::cout << tickersByExpiry << std::endl;
        }
        
        }
    
    }
    
    std::cout << "Size of tickersByExpiry for current snapshot: "<< tickersByExpiry.size() << std::endl;
    std::cout << tickersByExpiry << std::endl;
    

    std::map<datetime_t, std::pair<Smile, double>> res{};
    
    // then create Smile instance for each expiry by calling FitSmile() of the Smile
    // i.e. pass the data of each expiry to the FitSmile function in the smile model to fit the model to the market data, and calculate the fitting error
    
    // TODO: you need to implement FitSmile function in CubicSmile
    for (auto iter = tickersByExpiry.begin(); iter != tickersByExpiry.end(); iter++) {
//        auto sm = Smile::FitSmile(iter->first, iter->second);  
        auto results = Smile::FitSmile(iter->first, iter->second); 
        
        
        // TODO (Step 3): we need to measure the fitting error here
        // For simplicity, at this step we can take the average of BestBidIV and BestAskIV for fitting, without looking at other fields. 
        // You may start with equal weights for all the contracts, and refine weights later (optional).
        //The fitting error is defined as the mean (or weighted) square error of all the contracts’ mid implied volatility VS the model volatility at the corresponding strike.
        
        auto sm = std::get<0>(results);
        double fittingError = std::get<1>(results);
//        fittingError = SmileError(sm, strikeVolMap);
        
        res.insert(std::pair<datetime_t, std::pair<Smile, double>>{iter->first, std::pair<Smile, double>(sm, fittingError)});
        
    }
    return res;
}

#endif //QF633_CODE_VOLSURFBUILDER_H
