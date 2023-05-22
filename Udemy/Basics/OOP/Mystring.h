#ifndef _MYSTRING_H_
#define _MYSTRING_H_
#include <iostream>
#include <string>


class Mystring{
private:
    char *str;

public:
    Mystring();                         //No-arg constructor
    Mystring(const char *s);            //Overloaded constructor
    Mystring(const Mystring &source);   //Copy constructor
    ~Mystring();                        //Destructor
    
    
    //Overloading the copy assignment operator (deep copy)
    //Type &Type::operator=(const Type &rhs);
    Mystring &operator=(const Mystring &rhs); 
    
    void display() const;
    int get_length() const;
    const char *get_str() const;        //returns a constant pointer pointing to char

};


#endif // _MYSTRING_H_
