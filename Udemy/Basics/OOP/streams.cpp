#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

/* iostream: Provides definitions for formatte input and output from/to streams
 * fstream: Provides definitions for formatted input and output from/to FILE streams
 * iomanip: Provides definitions for manipulators used to format stream I/O
 * 
 * Commonly used stream classes
 * (1) ios
 * (2) ifstream     //fstream and ifstream are commonly used for input files
 * (3) ofstream
 * (4) fstream
 * (5) stringstream
 * 
 * Global Stream Objects
 * (1) cin
 * (2) cout
 * (3) cerr
 * (4) clog
 * Best practise is to use cerr for error messages and clog for log messages
*/ 



int main() {
    std::cout << "Hi 🤌" << std::endl;
    
    double num {1234.5678};
    
    std::cout << num << std::endl;  //output: 1234.57 (default precision is 6 and rounding)
    
    
    std::cout << "Trying setprecision" << std::endl;
    std::cout << std::setprecision(9);
    std::cout << num << std::endl;      //output: 1234.5678
    
    std::cout << "Try setprecision with fixed" << std::endl;
    std::cout << std::setprecision(3) << std::fixed;
    std::cout << num << std::endl;      //output: 1234.568 (precision 3 from the decimal)
    
    std::cout << "Resetting Format" << std::endl;
    std::cout << std::resetiosflags(std::ios::floatfield);
    std::cout << num << std::endl;
    
    std::cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> READING FROM A FILE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    
    std::ifstream in_file1;
    std::string line;
    int number;
    double total;
    
    
    in_file1.open("test.txt");
    if (!in_file1){
        std::cerr << "Problem opening file!!" << std::endl;
        return 1;
    }
    
    std::cout << "File is good to go!" << std::endl;
    
    while (!in_file1.eof()){
        in_file1 >> line >> number >> total;
        std::cout << std::setw(10) << std::left << line
                  << std::setw(10) << number
                  << std::setw(10) << total
                  << std::endl;
        
    }
    
//    in_file >> line;
//
//    std::getline(in_file, line);
//    std::cout << line << std::endl;
//    
//    in_file >> number >> total;
//    std::cout << line << number << total << std::endl;
    
    in_file1.close();
    
    
    std::ifstream in_file2;
    std::string movie_line {};
    
    in_file2.open("about_time.txt");
    
    if (!in_file2){
        std::cerr << "Problem opening file!!" << std::endl;
        
        return 1;
    }
    
    while (std::getline(in_file2, movie_line)) {
        std::cout << movie_line << std::endl;
    }
    
    
    std::ofstream out_file1 {"output.txt", std::ios::app};      //appending to file
    if (!out_file1){
        std::cerr << "Error creating file" << std::endl;
        return 1;
    }
    std::string write_line;
    std::cout << "Enter something to write to the file: ";
    std::getline(std::cin, line);   //cin >> line
    
    out_file1 << line << std::endl;     //write into file like this
    
    out_file1.close();
    
    return 0;
}