#include <iostream>
#include <cstring>
#include <vector>

#include "Mystring.h"

using namespace std;

/********************************************************************************************************************
 * What is Operator Overloading?
 * (1) Using taditional operator such as +, = , * etc etc WITH USER-DEFINED TYPES 
 * (2) Allows user-defined types to behave similar to built-in types
 * (3) Can make code more readable and writable
 * (4) Not done automatically (except for the assignment operator); they must be explicitly defined
 * (5) DON'T overload unless it makes sense
 * (6) [], (), -> and = MUST be declared as member methods
 ********************************************************************************************************************/ 

int main(){
    cout << "Welcome to Head Pain+++ \n";
    
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
    
 return 0;   
}