#ifndef QF633_CODE_MSG_H
#define QF633_CODE_MSG_H

#include <cstdint>
#include <string>
#include <vector>

//contractName,       Y
//time,               Y   //timestamp of the update, in UTC.
//msgType,            N read in for checks
//priceCcy,           N           
//bestBid,            Y
//bestBidAmount,      Y
//bestBidIV,          Y
//bestAsk,            Y
//bestAskAmount,      Y
//bestAskIV,          Y
//markPrice,          Y
//markIV,             Y
//underlyingIndex,    Y
//underlyingPrice,    Y
//interest_rate,      N
//lastPrice,          Y
//open_interest,      Y
//vega,               N
//theta,              N
//rho,                N
//gamma,              N
//delta               N

struct TickData {
    std::string ContractName;
//    std::string MsgType;
    
    double BestBidPrice;
    double BestBidAmount;
    double BestBidIV;
    double BestAskPrice;
    double BestAskAmount;
    double BestAskIV;
    double MarkPrice;
    double MarkIV;
    std::string UnderlyingIndex;
    double UnderlyingPrice;
    double LastPrice;
    double OpenInterest;
    uint64_t LastUpdateTimeStamp;
};

struct Msg {
    uint64_t timestamp{};
    bool isSnap;
    bool isSet = false;
    std::vector<TickData> Updates;
};

#endif //QF633_CODE_MSG_H
