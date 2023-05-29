#include <iostream>
#include <cstring>
#include <vector>

#include "Mystring.h"

using namespace std;

/********************************************************************************************************************
 * What is Operator Overloading?
 * (1) Using traditional operator such as +, = , * etc etc WITH USER-DEFINED TYPES 
 * (2) Allows user-defined types to behave similar to built-in types
 * (3) Can make code more readable and writable
 * (4) Not done automatically (except for the assignment operator); they must be explicitly defined
 * (5) DON'T overload unless it makes sense
 * (6) [], (), -> and = MUST be declared as member methods
 ********************************************************************************************************************/ 

int main(){
    cout << "Welcome to Head Pain+++ \n";
    
    cout << "Case #1: Using overloading constructor" << endl;
    Mystring a {"Hello!"};   //object a which has the str attribute pointing to "Hello" on the heap
    Mystring hi;
    
    cout << "Enter one word: " << endl;
    cin >> hi;
    
    cout << "It's me, " << hi << ", I'm the problem it's me." << endl;
    
    cout << "Case #2: Using overloading constructor then Move Assignment" << endl;
    a = Mystring {"Guten Tag!"}; //notice that rhs (temporary object) has no name == it is a R-value 
    //will use a copy assignment if there is no move assignment defined
    
    cout << "Case #3: Using overloading constructor then Move Assignment" << endl;
    a = {"HAIYA NI HAO!"}; //Again, notice that rhs (temporary object) - literal has no name == it is a R-value 
    
    cout << "------------------------------------------------------------------------\n";
    
    char *str {nullptr};
    
    str = new char[4];
    strcpy(str, "LEON");
    
    cout << "SERIOUS TESTING #1: " << str << endl;     //output: LEON
    cout << "SERIOUS TESTING #2: " << *str << endl;    //output: L  
    
    Mystring empty;
    Mystring larry {"Larry"};
    Mystring stooge {larry};    //copy constructor
    
    empty.display();
    larry.display();
    stooge.display();
    
    cout << "------------------------------------------------------------------------\n";
    //When passing a C-style string as a function argument, 
    //it is common to pass it as a pointer to the first character of the string.
    Mystring s1 {"Leon"}; //char *s
//    Mystring s2 = s1;   //this is not assignment but same as Mystring s2 {s1}; copy constructor
    Mystring s2;
    
    //OBJECT = OBJECT 
    s2 = s1;    //the operator = here will be using the overloading operation
    //i.e. s2.operator=(s1) == the operator= method is called
    cout << "s2 = s1 gives s2=" << s2.get_str() << endl;
    s2.display();
//    s2 = s1;    //compiler will actually convert this statement to s2.operator=(s1);
    
    
    cout << "------------------------------------------------------------------------\n";
    cout << "Other overloading operators as member functions";
    
    cout << boolalpha << endl;
    
    Mystring leon {"Leon"};
    Mystring loki {"Loki"};
    
    Mystring gang = leon;    //will trigger copy assignment!
    leon.display();
    loki.display();
    gang.display();
    
    cout << (leon == loki) << endl;
    cout << (leon == gang) << endl;
    
    leon.display();
    Mystring leon2 = -leon;
    leon2.display();
    
    Mystring test = leon+ loki ; //this one ok
    test.display();
    
    Mystring gangsters = leon + loki.get_str();   //can? YES
    
    Mystring two_teen_gang = loki + " " + leon;
    two_teen_gang.display();
        
    Mystring three_teen_gang = loki + " " + leon + " " + "Lemon";
    three_teen_gang.display();

 return 0;   
}