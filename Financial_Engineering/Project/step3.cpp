#include <iostream>

#include "CsvFeeder.h"
#include "Msg.h"
#include "VolSurfBuilder.h"
#include "CubicSmile.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: "
                  << argv[0] << " tick_data.csv" << " outputFile.csv" << std::endl;
        return 1;
    }
    const char* ticker_filename = argv[1];
    const char* output_filename = argv[2];
    
    std::ofstream outputFile(output_filename, std::ios::trunc);
//    std::ofstream outputFile;

    VolSurfBuilder<CubicSmile> volBuilder;
    auto feeder_listener = [&volBuilder] (const Msg& msg) {
        if (msg.isSet) {
//            std::cout << msg.timestamp << ", isSnap = " << msg.isSnap << ", numUpdates = " << msg.Updates.size() << std::endl;
            volBuilder.Process(msg);
        }
    };

//    auto timer_listener = [&volBuilder, &outputFile] (uint64_t now_ms) {
    auto timer_listener = [&] (uint64_t now_ms) {
        // fit smile
//        volBuilder.PrintInfo();
        auto smiles = volBuilder.FitSmiles(); //returns std::map<datetime_t, std::pair<Smile, double>>
        
        std::ofstream outputFile(output_filename, std::ios::trunc); //only keep latest snapshot
        // TODO: stream the smiles and their fitting error to outputFile.csv
        if (outputFile.is_open()){
            bool isEmpty = outputFile.tellp() == 0;
            
            if (isEmpty){
            outputFile << "TIME" << "," << "EXPIRY" << "," << "MATURTIES" << "," << "FUT_PRICE" <<"," << "ATM" <<"," << "BF25" << ","  << "RR25" 
                    << ","  << "BF10" <<","  << "RR10" << "," << "FITTING_ERROR" 
                    << ","  << "K_QD90" << ","  << "K_QD75" << ","  << "K_QD25" << ","  << "K_QD10" << std::endl;
//            outputFile << "OKAY EVERYTHING IS UNDER CONTROL" << std::endl;
            }

            for (auto itr = smiles.begin(); itr != smiles.end(); itr++){
                auto strikeMarks_vec = (itr->second).first.strikeMarks;
                double bf25 = (strikeMarks_vec.at(1).second + strikeMarks_vec.at(3).second)/2 - strikeMarks_vec.at(2).second;
                double rr25 = strikeMarks_vec.at(3).second - strikeMarks_vec.at(1).second;
                double bf10 = (strikeMarks_vec.at(0).second + strikeMarks_vec.at(4).second)/2 - strikeMarks_vec.at(2).second;
                double rr10 = strikeMarks_vec.at(4).second - strikeMarks_vec.at(0).second;
                
                double k_qd90 = (itr->second).first.strikeMarks.at(0).first;
                double k_qd75 = (itr->second).first.strikeMarks.at(1).first;
                double fwd = (itr->second).first.strikeMarks.at(2).first;
                double k_qd25 = (itr->second).first.strikeMarks.at(3).first;
                double k_qd10 = (itr->second).first.strikeMarks.at(4).first;
                
                double T = itr->first - datetime_t(now_ms) + 1.0/365;
//                std::cout << "CHECK TtM: " << T << std::endl;
                
                outputFile << datetime_t(now_ms) << "," << itr->first << ","  << T << "," << fwd << "," << strikeMarks_vec.at(2).second << "," 
                        << bf25 << ","  << rr25 << ","  << bf10 << ","  << rr10 << "," << (itr->second).second << "," 
                        << k_qd90 << "," << k_qd75 << "," << k_qd25 << "," << k_qd10 << std::endl;
                
            }
//            outputFile.close();
            std::cout << "Data written to output.csv" << std::endl;
        }

        else {
            std::cout << "Failed to open the file." << std::endl;
        }
    };


    const auto interval = std::chrono::minutes(1);  // we call timer_listener at 1 minute interval
    CsvFeeder csv_feeder(ticker_filename,
                         feeder_listener,
                         interval,
                         timer_listener);
                         
    while (csv_feeder.Step()) {}
    
    return 0;
}
