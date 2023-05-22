#include <cstring> //Note that C-style strings are arrays of characters where the last character is always a null character,
                   //indicating the end of the string
#include <iostream>
#include "Mystring.h"


Mystring::Mystring()
    : str {nullptr}{
        str = new char[1];
        *str = '\0';        //represents null string (marks the end of a string)
}


Mystring::Mystring(const char *s)
    : str {nullptr}{
        if (s == nullptr){
            str = new char[1];
            *str = '\0';
        }
        else {
            str = new char[std::strlen(s) + 1];
            std::strcpy(str, s);
        }
}
    
Mystring::Mystring(const Mystring &source)
    : str {nullptr}{
        str = new char[std::strlen(source.str)+1];
        std::strcpy(str, source.str);
    }
    

Mystring::~Mystring(){
    delete [] str;
}

//Copy assignment
Mystring &Mystring::operator=(const Mystring &rhs) {
    std::cout << "Copy assignment" << std::endl;
    
    if (this == &rhs)   //checking for self assignment e.g. p1 = p1;
        return *this;   //return current object
        
    delete [] this->str;  //deallocate storage for this->str (LHS) since we are overwriting it
    
    str = new char[strlen(rhs.str) + 1];    //lhs ready to be assign by the data on rhs, thus allocate storage first
    strcpy(this->str, rhs.str);   //perform the copy
    
    return *this; //return the dereferenced this
}


//Display method
void Mystring::display() const{
    std::cout << str << ":" << get_length() << std::endl;
}

//Length getter
int Mystring::get_length() const {return std::strlen(str);}

//String getter
const char *Mystring::get_str() const {return str;}

