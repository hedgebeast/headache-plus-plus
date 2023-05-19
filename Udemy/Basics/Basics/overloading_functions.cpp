#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print(const int);
void print(const double);
void print(const string = "Please enter something to print!");
void print(const string, const string);
void print(const vector<string>);

void print(const int numbers [], size_t); //pass array to a function

int main(){
    
    print(); 
    
    print(100);
    print('A'); //character will be promoted to int
    
    print(123.5);
    print(123.2F); //float is promoted to double
    
    print("C-style string"); //C-style string is converted to c++ string
    
    string s{"C++ string"};
    print(s);
    
    print("C-style string", s);
    
    vector<string> three_names {"lol", "lame", "died"};
    print(three_names);
    
    cout << endl;
    
    int numbers[] {1,2,3,4,5};
    print(numbers, size(numbers));
    
    return 0;
}

void print(const int x){
    cout << "Printing int: " << x << endl;
}

void print(const double x){
    cout << "Printing double: " << x << endl;
}

void print(const string s){
    cout << "Printing string: " << s << endl;
}

void print(const string s, const string t){
    cout << "Printing 2 strings: " << s << " and " << t << endl;
}

void print(const vector<string> v){
    cout << "Printing vector of strings: ";
    for (auto s:v)
        cout << s + " ";
    cout << endl;
}

void print(const int numbers [], size_t size){
//    cout << size << endl;
    for (size_t i {0}; i< size; ++i)
        cout << numbers[i] << " ";
    cout << endl;
}