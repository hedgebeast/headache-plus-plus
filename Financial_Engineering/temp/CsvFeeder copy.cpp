#include <iostream>
#include "CsvFeeder.h"
#include "date/date.h"

#include <string>
#include <unordered_map>

uint64_t TimeToUnixMS(std::string ts) {
    std::istringstream in{ts};
    std::chrono::system_clock::time_point tp;
    in >> date::parse("%FT%T", tp);
    const auto timestamp = std::chrono::time_point_cast<std::chrono::milliseconds>(tp).time_since_epoch().count();
    return timestamp;
}


bool ReadNextMsg(std::ifstream& file, Msg& msg, Msg& diffMsg) {    
    int counter {0};
    
    if (file.eof()) {
        return false;
    }
    
    // reading the next msg
    if (diffMsg.isSet == true){
        msg = diffMsg;
        diffMsg = Msg();
        counter++;
    }
    
    // TODO: your implementation to read file and create the next Msg into the variable msg
    // Read the header row
    static std::unordered_map<std::string, int> columnMap; // Map to store column name to index mapping
    std::string header;
    
    if (file.is_open()){
        
        if (counter == 0) {
            if (std::getline(file, header)) {
                std::stringstream ss(header);
                std::string columnName;
                int columnIndex = 0;

                while (std::getline(ss, columnName, ',')) {
                    columnMap[columnName] = columnIndex;
                    columnIndex++;
                }
            }
        }
        
        // Read data (Data are sorted using Python i.e. df.sort_values(by='time', ascending=True))
        TickData tickData_;
        std::string line;
        
        while (std::getline(file, line)) {
            std::unordered_map<std::string, std::string> rowData;
            std::stringstream ss(line);
            std::string value;
            int columnIndex = 0;

            while (std::getline(ss, value, ',')) {
                // Find the corresponding column name based on the current index
                auto columnIter = std::find_if(columnMap.begin(), columnMap.end(), 
                    [&](const auto& pair) { return pair.second == columnIndex;});

                if (columnIter != columnMap.end()) {
                    std::string columnName = columnIter->first;
                    rowData[columnName] = value;
                }

                columnIndex++;
            }
            
            tickData_.ContractName = rowData["contractName"];
            tickData_.LastUpdateTimeStamp = TimeToUnixMS(rowData["time"]);    
            tickData_.BestBidPrice = (rowData["bestBid"].empty()) ? std::numeric_limits<double>::quiet_NaN() : stod(rowData["bestBid"]);
            tickData_.BestBidAmount = (rowData["bestBidAmount"].empty()) ? std::numeric_limits<double>::quiet_NaN() : stod(rowData["bestBidAmount"]);
            tickData_.BestBidIV = (rowData["bestBidIV"].empty()) ? std::numeric_limits<double>::quiet_NaN() : stod(rowData["bestBidIV"]);
            tickData_.BestAskPrice = (rowData["bestAsk"].empty()) ? std::numeric_limits<double>::quiet_NaN() : stod(rowData["bestAsk"]);
            tickData_.BestAskAmount = (rowData["bestAskAmount"].empty()) ? std::numeric_limits<double>::quiet_NaN() : stod(rowData["bestAskAmount"]);
            tickData_.BestAskIV = (rowData["bestAskIV"].empty()) ? std::numeric_limits<double>::quiet_NaN() : stod(rowData["bestAskIV"]);
            tickData_.MarkPrice = (rowData["markPrice"].empty()) ? std::numeric_limits<double>::quiet_NaN() : stod(rowData["markPrice"]);
            tickData_.MarkIV = (rowData["markIV"].empty()) ? std::numeric_limits<double>::quiet_NaN() : stod(rowData["markIV"]);
            tickData_.UnderlyingIndex = rowData["underlyingIndex"];
            tickData_.UnderlyingPrice = (rowData["underlyingPrice"].empty()) ? std::numeric_limits<double>::quiet_NaN() : stod(rowData["underlyingPrice"]);
            
            //checked in csv that only lastPrice column has null value 
            tickData_.LastPrice = (rowData["lastPrice"].empty()) ? std::numeric_limits<double>::quiet_NaN() : stod(rowData["lastPrice"]);    
       
            tickData_.OpenInterest = (rowData["open_interest"].empty()) ? std::numeric_limits<double>::quiet_NaN() : stod(rowData["open_interest"]);
            
//            std::cout << "QUICK CHECK! Contract here: " << rowData["contractName"] << " and timestamp: " << rowData["time"] << std::endl;
            
    /*        Note: Multiple rows in the csv files that has exactly the same timestamp is considered as one Msg. 
              ReadNextMsg() should load a complete Msg until timestamp changes. 
    */
            if (counter == 0){      //the very first data row
                msg.timestamp = tickData_.LastUpdateTimeStamp;
                if (rowData["msgType"] == "update")
                    msg.isSnap = false;
                else
                    msg.isSnap = true;
                    
                msg.Updates.push_back(tickData_);
                msg.isSet=true;    //loaded a msg
            }
            
            else if (counter > 0 && msg.timestamp == tickData_.LastUpdateTimeStamp){
                msg.Updates.push_back(tickData_);
            }
            
            else if (counter > 0 && msg.timestamp != tickData_.LastUpdateTimeStamp){
                diffMsg.timestamp = tickData_.LastUpdateTimeStamp;
                if (rowData["msgType"] == "update")
                    diffMsg.isSnap = false;
                else
                    diffMsg.isSnap = true;
                
                diffMsg.Updates.push_back(tickData_);
                diffMsg.isSet = true;

                return true;
            }
            else
                std::cerr << "Trouble reading message!" << std::endl;
            
            counter++;
        }
    }
    else
        std::cout << "Could not open the file" << std::endl;
    
    file.close();    
    return true;
}


CsvFeeder::CsvFeeder(const std::string ticker_filename,
                     FeedListener feed_listener,
                     std::chrono::minutes interval,
                     TimerListener timer_listener)
        : ticker_file_(ticker_filename),
          feed_listener_(feed_listener),
          interval_(interval),
          timer_listener_(timer_listener) {
    // initialize member variables with input information, prepare for Step() processing
    
    
    ReadNextMsg(ticker_file_, msg_, diffMsg_);
    
    if (msg_.isSet) {
        // initialize interval timer now_ms_
//        now_ms_ = new uint64_t;
//        *now_ms_ = msg_.timestamp;
        now_ms_ = msg_.timestamp;
        
    } 
    else 
        throw std::invalid_argument("empty message at initialization");
}


bool CsvFeeder::Step() {
    if (msg_.isSet) {
//        std::cout << "Finding Contract: " << msg_.Updates[0].ContractName << std::endl;
//        std::cout << "Finding Message Size: " << msg_.Updates.size() << std::endl;
        
        // call feed_listener with the loaded Msg
        feed_listener_(msg_);

        // if current message's timestamp is crossing the given interval, call time_listener, change now_ms_ to the next interval cutoff
//        if (*now_ms_ < msg_.timestamp) {
//            std::cout<< "Change INTERVAL PLACE! now_ms = " << *now_ms_ << ", msg timestamp = " << msg_.timestamp << std::endl;
//            timer_listener_(*now_ms_);
//            *now_ms_ += interval_.count();
//        }

        if (now_ms_ < msg_.timestamp) {
            std::cout<< "Change INTERVAL PLACE! now_ms = " << now_ms_ << ", msg timestamp = " << msg_.timestamp << std::endl;
            timer_listener_(now_ms_);
            
            now_ms_ += interval_.count();
        }
        // load tick data into Msg
        // if there is no more message from the csv file, return false, otherwise true
        return ReadNextMsg(ticker_file_, msg_, diffMsg_);
    }
    
//    delete now_ms_;
    return false;
}

CsvFeeder::~CsvFeeder() {
    // release resource allocated in constructor, if any
}