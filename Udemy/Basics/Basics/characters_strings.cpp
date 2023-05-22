#include <iostream>
#include <iomanip> //input-output manipulation

#include <cctype> //for character-based functions; allow the testing of characters for various properties & converting character case
#include <cstring> //for c-style string functions
#include <string> //A class in the Standard Template Library (STL)

#include <cstdlib> //convert C-style Strings to other types

#include <vector>

using namespace std; 

void pass_by_value(vector<string> v){
    v.clear(); //delete all vector elements
}

void print_vector(vector<string> v){
    for (auto s:v) //The auto keyword is a simple way to declare a variable that has a complicated type. 
    //For example, you can use auto to declare a variable where the initialization expression involves templates, 
    //pointers to functions, or pointers to members.
        cout << s << " ";
    cout << endl;
}

// Function that counts the length of a string
int stringLength(const char* str) {
    int length = 0;
    
    while (*str != '\0') {
        length++;
        str++;
    }
    
    return length;
}

// C++ supports 2 types of strings: c-style strings and c++ strings
int main() {
    
    char my_name[12];    
    
    int test_int[5] {1,2,3,4,5};
    cout << "TESTING: " << test_int << endl;    //returns address of test_int[0]
    
    string test_str[3] {"e", "ed", "eddy"};
    cout << "TESTING: " << test_str << endl;    //returns address of test_str[0]
    
//    my_name = "Leon"; //Error: array type 'char [8]' is not assignable
    
    strcpy(my_name, "Leon");
    cout << "TESTING: " << my_name << endl;     //returns the whole cstring
    cout << my_name[0] << my_name[1] << my_name[2] << my_name[3] << endl;
    
    strcat(my_name, " ");
    strcat(my_name, "Avocado");
    
    cout << strlen(my_name) << endl;    
    
    cout << boolalpha;
    cout << (100 == 100) << endl;
//    cout << strcmp(my_name, "Leon Avocado") << endl;
    if (strcmp(my_name, "Leon Avocado") == 0)
        cout << "same la sia" << endl;
    else 
        cout << "thank you next" << endl;
    
    
    cout << my_name << endl;
    
    cout << "------------------------------------------------------------------------\n";
//    const char* myString {"Hello, world!"};
    
    // Pass the string as a pointer to the function
    int length = stringLength("Hello, world!");  
    
    cout << "Length of the string: " << length << std::endl;
    cout << "------------------------------------------------------------------------\n";
    
    char full_name [50] {};
    cout << "Welcome to Heachache++!" << endl;
    cout << "Enter your full name stranger: ";
    cin.getline(full_name, 50);
    cout << "Oh! You are " << full_name << endl;
    
    for(size_t i{0}; i < strlen(full_name); ++i){
        if(isalpha(full_name[i]))
            full_name[i] = toupper(full_name[i]);
    }
    cout << "Your full name is " << full_name << endl;
    
    string s1; //can ASSIGN string :)
    cout << "Empty string: " << s1 << endl; //no garbage output
    
    string s2 = "FINALLY can assign!!";
    cout << "String: " << s2 << endl;
    
    string s3 {"Frank"};
    for (char c: s3)
        cout << c;
    cout << endl;
    
    cout << "--------------------------------" << endl;
    
    for(size_t i {0}; i < s3.length(); ++i)
        cout << s3.at(i);
    cout << endl;
        
    cout << s3.substr(0,3) << endl; //output: Fra
    cout<< s3.length() << endl;
    
    //s3.find("an");
    //s3.erase(0,3); or clear everything s3.clear()
    
    //Note the difference below:
    
    string s4;
    cout << "Enter \'Hello there\' please: " << endl;
//    cin >> s4; //enter Hello there
//    cout << s4 << endl; //output: Hello
    
    getline(cin, s4);
    cout << "Output with getline: " << s4 << endl; //output: Hello there
    
    vector<string> fruit_list {"Apple", "Banana", "Cucumber"};
    
    pass_by_value(fruit_list);
    print_vector(fruit_list);

    return 0;
}