#include "CubicSmile.h"
#include "BSAnalytics.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <map>

//To construct the smile (k −> σ) from the model parameters
//Obtain the strikes of the 5 QD points: K = Fe^{−N^(−1)(QD) × σ_ATM × √T}
//CubicSmile CubicSmile::FitSmile(const datetime_t& expiryDate, const std::vector<TickData>& volTickerSnap) {
std::tuple<CubicSmile, double> CubicSmile::FitSmile(const datetime_t& expiryDate, const std::vector<TickData>& volTickerSnap) {
    double fwd, T, bf25, rr25, bf10, rr10 = 0.0;
//    double atmvol {0.25}; //hard code first
    double interpolated_atmvol{0.0};
//    std::cout<< "expiryDate: " << expiryDate <<std::endl;
    
    // TODO (step 3): fit a CubicSmile that is close to the raw tickers
    // - make sure all tickData are on the same expiry and same underlying (reading csv with the all the same underlying)
    
    TickData LatestTick{};
    datetime_t latestTimeStamp {0};
    double strike {0};
    
    for (auto itr = volTickerSnap.begin(); itr != volTickerSnap.end(); itr++){
        TickData tempTick = *itr;
//        std::cout<< "LastUpdateTimeStamp: " << tempTick.LastUpdateTimeStamp <<std::endl;
        
        if (latestTimeStamp < tempTick.LastUpdateTimeStamp){    //overloaded in date.cpp
            latestTimeStamp = tempTick.LastUpdateTimeStamp;
//            std::cout<< "latestTimeStamp: " << latestTimeStamp <<std::endl;
            
            LatestTick = *itr;
        }
    }
    
    // get latest underlying price from all tickers based on LastUpdateTimeStamp
    fwd = LatestTick.UnderlyingPrice;
    
//    // get time to expiry T 
    T = expiryDate - latestTimeStamp + 1.0/365; //if at the last update time == expiry date (i take it as end of the day settlement thus + 1 day)
//    std::cout<< "TIME TO MATURITY: " << T << std::endl;
    
//    if (T <= 0) {
//        std::cout << "Expired Contracts on " << expiryDate << std::endl;
//        return CubicSmile();
//    }
    
    // get strike 
    map<double,double> strikePriceMap {};
    map<double,double> strikeVolMap {};
//    map<double,string> strikeTypeMap {};  //never use; decided to model using puts
    
    for (auto itr = volTickerSnap.begin(); itr != volTickerSnap.end(); itr++){
        TickData tempTick = *itr;
        std::istringstream iss {tempTick.ContractName};
        std::string string_strike;
        std::string string_optType;
        double strike, midPrice, midIV;
        
        
        
        for (int i = 0; i < 3; ++i) {
            std::getline(iss, string_strike, '-');
        }
        
        strike = std::stod(string_strike);
//        std::cout << "STRIKE: " << strike <<  " FORWARD: " << fwd << std::endl;
        
        midPrice = tempTick.MarkPrice;     //markPrice: we can consider this as the mid price
        //For simplicity, take contracts’ mid implied volatility as the average of BestBidIV and BestAskIV for fitting
        midIV = (tempTick.BestBidIV + tempTick.BestAskIV) / 2 / 100;   

        //(1) Gather the option market data: Collect the option prices (both call and put options) 
        //for different strike prices and the corresponding implied volatilities. 
        //Ensure that you have data for options with the same expiry date.
        

        std::getline(iss, string_optType, '-');
//        std::cout << "optType: " << string_optType << std::endl;
        
        auto strike_price = std::pair<double,double>(strike, midPrice);
        auto strike_impliedVol = std::pair<double,double>(strike, midIV);
//        auto strike_type = std::pair<double,string>(strike, string_optType);
        
        if (strike_price.second != 0 && string_optType == "C") {    //modeling using call options
            strikePriceMap.insert(strike_price);
//            strikeTypeMap.insert(strike_type);
            
            if (strike_impliedVol.second != 0) {
                strikeVolMap.insert(strike_impliedVol);
            }         
        }
    }
        
    //(2) FIND ATM VOL! (BRUTE FORCE - need to interpolate since cannot find contract that has strike ~= forward)
    
    double error {1};
    double temp_err {0};
    int n {30000};  //max(markIV) ~= 300
//    int n {250};
    
    double strikeLower_50, price_50, undiscPrice_50 = 0.0;
    
    for (int i = 1; i <= n; i++){
        double j = i/10000.0; //increment by 0.01%
//        double j = i/100.0;
        double stdev = j * sqrt(T);
//        std::cout << "stdev: " << stdev << std::endl;

        //Find ATM strike using quickDeltaToStrike function
        double k_qd50 = quickDeltaToStrike(0.5, fwd, stdev);
//        std::cout << "k_qd50: " << k_qd50 << std::endl << std::endl;

        //Interpolate observed market prices (instead of interpolating implied vol directly)
        //Linear interpolation: y = y1 + (x - x1) * (y2 - y1) / (x2 - x1)

        for (auto itr = strikePriceMap.begin(); itr != strikePriceMap.end(); itr++){
            if (itr == strikePriceMap.begin()){
                strikeLower_50 = (*itr).first;
                price_50 = (*itr).second;
                continue; 
            }
          
            if (k_qd50 >= strikeLower_50 && k_qd50 <= itr->first){
//                std::cout << "price_50: " << price_50 << std::endl;
                undiscPrice_50 = (price_50 + (k_qd50 - strikeLower_50) * (itr->second - price_50) / (itr->first - strikeLower_50))*fwd; //markPrice is in unit of BTC
//                std::cout << "undiscPrice_50: " << undiscPrice_50 << std::endl;
            }
            
            strikeLower_50 = itr->first;
            price_50 = itr->second;
        }
                

        temp_err = std::abs(bsUndisc(Call, k_qd50, fwd, T, j) - undiscPrice_50)/undiscPrice_50;  //finding relative error for simplicity
            
        if (temp_err < error){
            error = temp_err;
            interpolated_atmvol = j;
//            std::cout << "ERROR: " << error << std::endl;
//            std::cout << "INSIDE interpolated_atmvol: " << interpolated_atmvol << std::endl;
        }
    
    }
    std::cout << "ERROR: " << error << std::endl;
    std::cout << "ATMVOL: " << interpolated_atmvol << std::endl;
    
    /* -------------------------- INSIDE BSANALYSTICS.H --------------------------
     * // qd = N(log(F/K) / stdev), so K = F / exp((N^{-1}(qd) * stdev))
     
        double quickDeltaToStrike(double qd, double fwd, double stdev) {
            double inv = invcnorm(qd);
            return fwd / std::exp(inv * stdev);
        }

        double quickDeltaToStrike(double qd, double fwd, double atmvol, double T) {
            double stdev = atmvol * sqrt(T);
            return quickDeltaToStrike(qd, fwd, stdev);
        }
         
        double bsUndisc(OptionType optType, double k, double fwd, double T, double sigma) {
        double sigmaSqrtT = sigma * std::sqrt(T);
        double d1 = std::log(fwd / k)/sigmaSqrtT + 0.5 * sigmaSqrtT;
        double d2 = d1 - sigmaSqrtT;
        double V_0;
        switch (optType)
        {
            case Call:
                V_0 = fwd * cnorm(d1) - k * cnorm(d2);
                break;
            case Put:
                V_0 = k * cnorm(-d2) - fwd * cnorm(-d1);
                break;
            default:
                throw "unsupported optionType";
        }
        return V_0;
        }
    
        double impliedVol(OptionType optionType, double k, double fwd, double T, double undiscPrice) {
            auto f = [undiscPrice, optionType, k, fwd, T](double vol){return bsUndisc(optionType, k, fwd, T, vol) - undiscPrice;};
            return rfbrent(f, 1e-4, 10, 1e-6);
        }
    ----------------------------------------------------------------------------*/ 
    
    // - fit the 5 parameters of the smile, atmvol, bf25, rr25, bf10, and rr10 using L-BFGS-B solver, to the ticker data
    
    double strikeLower_90, price_90, undiscPrice_90 = 0.0;
    double strikeLower_75, price_75, undiscPrice_75 = 0.0;
    double strikeLower_25, price_25, undiscPrice_25 = 0.0;
    double strikeLower_10, price_10, undiscPrice_10 = 0.0;
    double stdev = interpolated_atmvol * sqrt(T);

    double k_qd90 = quickDeltaToStrike(0.9, fwd, stdev);
    double k_qd75 = quickDeltaToStrike(0.75, fwd, stdev);
    double k_qd50 = quickDeltaToStrike(0.5, fwd, stdev);
    double k_qd25 = quickDeltaToStrike(0.25, fwd, stdev);
    double k_qd10 = quickDeltaToStrike(0.1, fwd, stdev);
    
    std::cout << "For Expiry: " << expiryDate << std::endl;
    std::cout << "k_qd90: " << k_qd90 << ", "
              << "k_qd75: " << k_qd75 << ", "
              << "k_qd50: " << k_qd50 << ", "
              << "k_qd25: " << k_qd25 << ", "
              << "k_qd10: " << k_qd10 << ", "
              << std::endl; 
              
    for (auto iter = strikePriceMap.begin(); iter != strikePriceMap.end(); iter++){
        
        if (iter == strikePriceMap.begin()){
            strikeLower_90 = iter->first;
            strikeLower_75 = iter->first;
            strikeLower_25 = iter->first;
            strikeLower_10 = iter->first;
            price_90 = iter->second;
            price_75 = iter->second;
            price_25 = iter->second;
            price_10 = iter->second;
            
            continue; 
        }
        
        if (k_qd90 >= strikeLower_90 && k_qd90 <= iter->first)
            undiscPrice_90 = (price_90 + (k_qd90 - strikeLower_90) * (iter->second - price_90) / (iter->first - strikeLower_90))*fwd;
        
        if (k_qd75 >= strikeLower_75 && k_qd75 <= iter->first)
            undiscPrice_75 = (price_75 + (k_qd75 - strikeLower_75) * (iter->second - price_75) / (iter->first - strikeLower_75))*fwd;
        
        if (k_qd25 >= strikeLower_25 && k_qd25 <= iter->first)
            undiscPrice_25 = (price_25 + (k_qd25 - strikeLower_25) * (iter->second - price_25) / (iter->first - strikeLower_25))*fwd;
        
        if (k_qd10 >= strikeLower_10 && k_qd10 <= iter->first)
            undiscPrice_10 = (price_10 + (k_qd10 - strikeLower_10) * (iter->second - price_10) / (iter->first - strikeLower_10))*fwd;
        
        strikeLower_90 = iter->first;
        strikeLower_75 = iter->first;
        strikeLower_25 = iter->first;
        strikeLower_10 = iter->first;
        price_90 = iter->second;
        price_75 = iter->second;
        price_25 = iter->second;
        price_10 = iter->second;
    }
    
    // using interpolated market observed price to find model impliedVol
//    double sigma_90 = impliedVol(Put, k_qd90, fwd, T, undiscPrice_90);
//    double sigma_75 = impliedVol(Put, k_qd75, fwd, T, undiscPrice_75);
//    double sigma_25 = impliedVol(Put, k_qd25, fwd, T, undiscPrice_25);
//    double sigma_10 = impliedVol(Put, k_qd10, fwd, T, undiscPrice_10);
    
    double sigma_90 = impliedVol(Call, k_qd90, fwd, T, undiscPrice_90);
    double sigma_75 = impliedVol(Call, k_qd75, fwd, T, undiscPrice_75);
    double sigma_25 = impliedVol(Call, k_qd25, fwd, T, undiscPrice_25);
    double sigma_10 = impliedVol(Call, k_qd10, fwd, T, undiscPrice_10);

    bf25 = (sigma_75+sigma_25)/2 - interpolated_atmvol;
    bf10 = (sigma_90+sigma_10)/2 - interpolated_atmvol;
    rr25 = sigma_25-sigma_75;
    rr10 = sigma_10-sigma_90;
    
    std::cout << "F = " << fwd << ", T = "<< T << ", ATMVOL = " << interpolated_atmvol << ", bf25 = " << bf25 
                << ", rr25 = " << rr25 << ", bf10 = " << bf10 << ", rr10 = " << rr10 << std::endl << std::endl; 
    
    // after the fitting, we can return the resulting smile
    
    auto sm = CubicSmile(fwd, T, interpolated_atmvol, bf25, rr25, bf10, rr10);
    double err = SmileError(sm, strikeVolMap);
    
//    return CubicSmile(fwd, T, interpolated_atmvol, bf25, rr25, bf10, rr10);
    return std::make_tuple(sm, err);
}


CubicSmile::CubicSmile(double underlyingPrice, double T, double atmvol, double bf25, double rr25, double bf10, double rr10) {
    // convert delta marks to strike vol marks, setup strikeMarks, then call BuildInterp
    double v_qd90 = atmvol + bf10 - rr10 / 2.0;
    double v_qd75 = atmvol + bf25 - rr25 / 2.0;
    double v_qd25 = atmvol + bf25 + rr25 / 2.0;     //formula is for Call
    double v_qd10 = atmvol + bf10 + rr10 / 2.0;

    // we use quick delta: qd = N(log(F/K / (atmvol) / sqrt(T))
    double stdev = atmvol * sqrt(T);
    double k_qd90 = quickDeltaToStrike(0.90, underlyingPrice, stdev);
    double k_qd75 = quickDeltaToStrike(0.75, underlyingPrice, stdev);
    double k_qd25 = quickDeltaToStrike(0.25, underlyingPrice, stdev);
    double k_qd10 = quickDeltaToStrike(0.10, underlyingPrice, stdev);

    strikeMarks.push_back(std::pair<double, double>(k_qd90, v_qd90));
    strikeMarks.push_back(std::pair<double, double>(k_qd75, v_qd75));
    strikeMarks.push_back(std::pair<double, double>(underlyingPrice, atmvol));
    strikeMarks.push_back(std::pair<double, double>(k_qd25, v_qd25));
    strikeMarks.push_back(std::pair<double, double>(k_qd10, v_qd10));
    BuildInterp();
}

void CubicSmile::BuildInterp()
{
  int n = strikeMarks.size();
  // end y' are zero, flat extrapolation
  double yp1 = 0;
  double ypn = 0;
  y2.resize(n);
  vector<double> u(n-1);

  y2[0] = -0.5;
  u[0]=(3.0/(strikeMarks[1].first-strikeMarks[0].first)) *
    ((strikeMarks[1].second-strikeMarks[0].second) / (strikeMarks[1].first-strikeMarks[0].first) - yp1);

  for(int i = 1; i < n-1; i++) {
    double sig=(strikeMarks[i].first-strikeMarks[i-1].first)/(strikeMarks[i+1].first-strikeMarks[i-1].first);
    double p=sig*y2[i-1]+2.0;
    y2[i]=(sig-1.0)/p;
    u[i]=(strikeMarks[i+1].second-strikeMarks[i].second)/(strikeMarks[i+1].first-strikeMarks[i].first)
      - (strikeMarks[i].second-strikeMarks[i-1].second)/(strikeMarks[i].first-strikeMarks[i-1].first);
    u[i]=(6.0*u[i]/(strikeMarks[i+1].first-strikeMarks[i-1].first)-sig*u[i-1])/p;
  }

  double qn=0.5;
  double un=(3.0/(strikeMarks[n-1].first-strikeMarks[n-2].first)) *
    (ypn-(strikeMarks[n-1].second-strikeMarks[n-2].second)/(strikeMarks[n-1].first-strikeMarks[n-2].first));

  y2[n-1]=(un-qn*u[n-2])/(qn*y2[n-2]+1.0);

//  std::cout << "y2[" << n-1 << "] = " << y2[n-1] << std::endl;
  for (int i=n-2;i>=0;i--) {
    y2[i]=y2[i]*y2[i+1]+u[i];
//    std::cout << "y2[" << i << "] = " << y2[i] << std::endl;
  }
}

double CubicSmile::Vol(double strike) {
  unsigned i;
  // we use trivial search, but can consider binary search for better performance
  for (i = 0; i < strikeMarks.size(); i++ )
    if (strike < strikeMarks[i].first )
      break; // i stores the index of the right end of the bracket

  // extrapolation
  if (i == 0)
    return strikeMarks[i].second;
  if (i == strikeMarks.size() )
    return strikeMarks[i-1].second;

  // interpolate
  double h = strikeMarks[i].first - strikeMarks[i-1].first;
  double a = (strikeMarks[i].first - strike) / h;
  double b = 1 - a;
  double c = (a*a*a - a) * h * h / 6.0;
  double d = (b*b*b - b) * h * h / 6.0;
  
  return a*strikeMarks[i-1].second + b*strikeMarks[i].second + c*y2[i-1] + d*y2[i];
}


double SmileError(CubicSmile sm, map<double,double> strikeVolMap){
    //Calculate error
    double error {0.0};
    double strikeMarket, mktMidVol, modelVol = 0.0;
    double strike;


    for (auto iter = strikeVolMap.begin(); iter != strikeVolMap.end(); iter++){
        strikeMarket = iter->first;
        mktMidVol = iter->second;
        modelVol = sm.Vol(strikeMarket);
        error += std::pow((modelVol - mktMidVol), 2); // sum of squared error
    }
    
    return error/size(strikeVolMap);
}