#ifndef _ORDER_H_
#define _ORDER_H_

#include <string>
#include <iostream>


struct Order{
    
    Order (int price, int open_qty, const std::string &order_id, bool is_sell)
        : price(price), open_qty(open_qty), order_id(order_id), is_sell(is_sell) {}

    int price;               // the order's price, and int type used instead of double type for simplicity
    int open_qty;            // the open qty of the order
    std::string order_id;    // an unique order ID to identify the order 
    bool is_sell;            // order side, true - buy order, false - sell order
    
    bool operator<(const Order &rhs) const{
//        std::cout << this->order_id << ":" << this->price << " VS " << rhs.order_id << ":" << rhs.price << std::endl;        
        return this->price < rhs.price;
    }
    
    bool operator==(const std::string &rhs) const{
        return (this->order_id == rhs);
    }
    
    bool operator==(const Order &rhs) const{
        return (this->price == rhs.price);
    }
    

};

std::ostream& operator<<(std::ostream& os, const Order& order);



#endif // _ORDER_H_