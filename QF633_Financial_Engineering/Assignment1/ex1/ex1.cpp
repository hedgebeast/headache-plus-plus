#include <iostream>
#include <string>

using namespace std;

/* Done by: Leon Cai
 *- argc (argument count) represents the number of command line arguments passed to the program, 
 *  including the name of the program itself (if argc is equal to 1, we assume that no arguments were passed)
 *-  argv (argument vector) is an array of strings that contains the command line arguments.
 *   (The first argument (argv[0]) is always the name of the program itself)
*/

int main(int argc, char* argv[])
{
    string str;
    string lowercaseStr = "";
    
    char first_row[10] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'};
    char second_row[9] = {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'};
    char last_row[7] = {'z', 'x', 'c', 'v', 'b', 'n', 'm'};
//    cout << first_row[2] << endl;
    char first[10] = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'};
    char second[9] = {'.', '.', '.', '.', '.', '.', '.', '.', '.'};
    char last[7] = {'.', '.', '.', '.', '.', '.', '.'};
    
//    std::cout << argc << std::endl;
//    std::cout << argv[0] << " and " << argv[1] << std::endl;
    if (argc > 1) // check if command line argument is passed
    {
        str = argv[1];
    }
    else // prompt the user to enter input
    {
        cout << "Please enter a valid string: ";
        getline(cin, str);
    }

    cout << "You have keyed in: " << str << endl;
    
    // Convert string to lowercase
    for (char c : str) {
        lowercaseStr += tolower(c);
    }
    
    for (int i = 0; i < 10; i++) {
        for (char c : lowercaseStr){
//            cout << c << endl;
            if (c == first_row[i] && first[i] != 'o'){
                first[i] = 'o';
            }
        }
        cout << first[i] << " ";
    }
    cout << endl << " ";
    
    for (int i = 0; i < 9; i++) {
        for (char c : lowercaseStr){
//            cout << c << endl;
            if (c == second_row[i] && second[i] != 'o'){
                second[i] = 'o';
            }
        }
        cout << second[i] << " ";
    }
    cout << endl << "  ";
    
    for (int i = 0; i < 7; i++) {
        for (char c : lowercaseStr){
//            cout << c << endl;
            if (c == last_row[i] && last[i] != 'o'){
                last[i] = 'o';
            }
        }
        cout << last[i] << " ";
    }
    cout << endl;

    return 0;
}

