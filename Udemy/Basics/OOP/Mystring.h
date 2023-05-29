#ifndef _MYSTRING_H_
#define _MYSTRING_H_
//#include <iostream>
#include <string>


class Mystring{
//Overloading operators as Global Functions
//    friend bool operator==(const Mystring &lhs, const Mystring &rhs);
//    friend Mystring operator-(const Mystring &obj);
//    friend Mystring operator+(const Mystring &lhs, const Mystring &rhs);
    friend std::ostream &operator<<(std::ostream &os, const Mystring &rhs);
    friend std::istream &operator>>(std::istream &in, Mystring &rhs);
    
private:
    char *str;

public:
    Mystring();                         //No-arg constructor
    Mystring(const char *s);            //Overloaded constructor
    
    Mystring(const Mystring &source);   //Copy constructor
    Mystring(Mystring &&source);        //Move constructor
    
    ~Mystring();                        //Destructor
    
    
    //Overloading the copy assignment operator (deep copy)
    //Type &Type::operator=(const Type &rhs);
    Mystring &operator=(const Mystring &rhs);   //Copy assignment (works with L-value references)
    Mystring &operator=(Mystring &&rhs);        //Move assignment; can be more efficient (works with R-value references - temporary unnamed objects)
    
    //Other overloading operators!
    Mystring operator-() const; //unary operator; make lowercase
    Mystring operator+(const Mystring &rhs) const; //binary operator; concatenate
    bool operator==(const Mystring &rhs) const;
    
    
    void display() const;
    int get_length() const;
    const char *get_str() const;        //returns a constant pointer pointing to char

};


#endif // _MYSTRING_H_
