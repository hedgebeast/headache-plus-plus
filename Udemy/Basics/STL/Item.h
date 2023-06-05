#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>

template <typename T>
class Item {
private:
    std::string name;
    T value;
    
public:
    Item(std::string name, T value)
        : name {name}, value {value}{}
    
    std:: string get_name() const {return name;}
    T get_value() const {return value;}
};


template <typename T1, typename T2>
struct My_Pair{
    T1 first;
    T2 second;
};



#endif // _ITEM_H_
