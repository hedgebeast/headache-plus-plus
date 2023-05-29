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
//        std::cout << "** Using OVERLOADING Constructor **" << std::endl;
        if (s == nullptr){
            str = new char[1];
            *str = '\0';
        }
        else {
            str = new char[std::strlen(s) + 1];
            std::cout << s << std::endl;
            std::strcpy(str, s);
        }
}
    
Mystring::Mystring(const Mystring &source)
    : str {nullptr}{
        std::cout << "** Using COPY Constructor **" << std::endl;
        str = new char[std::strlen(source.str)+1];
        std::strcpy(str, source.str);
    }
    

Mystring::~Mystring(){
    delete [] str;
}

//Copy assignment
Mystring &Mystring::operator=(const Mystring &rhs) {
    std::cout << "** Using COPY Assignment **" << std::endl;
    
    if (this == &rhs)   //checking for self assignment e.g. p1 = p1;
        return *this;   //return current object
        
    delete [] this->str;  //deallocate storage for this->str (LHS) since we are overwriting it
    
    str = new char[strlen(rhs.str) + 1];    //lhs ready to be assign by the data on rhs, thus allocate storage first
    strcpy(this->str, rhs.str);   //perform the copy
    
    return *this; //return the dereferenced this
}

//Move assignment
Mystring &Mystring::operator=(Mystring &&rhs){
    std::cout << "** Using MOVE Assignment **" << std::endl;
    std::cout << "Initially, this str is pointing to: " << this->str << std::endl; //return "Hello"
    std::cout << "Initially, rhs str is pointing to: " << rhs.str << std::endl;
    
    if(this == &rhs)
        return *this;
        
    delete [] str; //delete pointing to "Hello"
    
    str = rhs.str;  //steal pointer
    rhs.str = nullptr;
    std::cout << "At the end, this str is pointing to: " << this->str << std::endl;
    std::cout << "At the end, rhs str is pointing to nullptr" << std::endl;
    return *this;
}

//Equality
bool Mystring::operator==(const Mystring &rhs) const {
    return (std::strcmp(str, rhs.str) == 0);
}

//Make lowercase
Mystring Mystring::operator-() const{
    char *buff = new char[std::strlen(str) + 1];
    std::strcpy(buff, str);
    for(size_t i {0}; i < std::strlen(buff); i++)
        buff[i] = std::tolower(buff[i]);
        
    Mystring temp {buff};
    delete [] buff;
    
    return temp;
}

//Concatenate
Mystring Mystring::operator+(const Mystring &rhs) const{
    char *buff = new char[std::strlen(str) + std::strlen(rhs.str) + 1];
    std::strcpy(buff, str);
    std::strcat(buff, rhs.str);
    
    Mystring temp {buff};
    delete [] buff;
    
    return temp;
}


/*------------------------------------------------------------------------------------------------------------------*/

//Display method
void Mystring::display() const{
    std::cout << str << ":" << get_length() << std::endl;
}

//Length getter
int Mystring::get_length() const {return std::strlen(str);}

//String getter
const char *Mystring::get_str() const {return str;}


/*//Example of overloading operators as Global Functions

//Equality
bool operator==(const Mystring &lhs, const Mystring &rhs){
    return (std::strcmp(lhs.str, rhs.str) == 0);
}

//Make Lowercase
Mystring operator-(const Mystring &obj){
    char *buff = new char[std::strlen(obj.str) + 1];
    strcpy(buff, obj.str);
    
    for (size_t i{0}; i<std::strlen(buff); i++)
        buff[i] = std::tolower(buff[i]);
        
    Mystring temp {buff};
    delete [] buff;
    
    return temp;
}

//Concatenation
Mystring operator+(const Mystring &lhs, const Mystring &rhs){
    char *buff = new char[std::strlen(lhs.str) + std::strlen(rhs.str) + 1];
    std::strcpy(buff, lhs.str);
    std::strcat(buff, rhs.str);
    
    Mystring temp {buff};
    delete [] buff;
    
    return temp;
}

*/

//overloaded insertion operator
std::ostream &operator<<(std::ostream &os, const Mystring &rhs){
    os << rhs.str;
    
    return os;
}


//overloaded extraction operator
std::istream &operator>>(std::istream &in, Mystring &rhs){
    char *buff = new char[1000];
//    char buff[101];
    in >> buff; //error: invalid operands to binary expression ('std::istream' (aka 'basic_istream<char>') and 'char *') - doesn't work for version above c++17
    
    std::cout << "What's in buff?? " << buff << std::endl;
    
    rhs = Mystring{buff};
    
    delete [] buff;
    
    return in;
}
