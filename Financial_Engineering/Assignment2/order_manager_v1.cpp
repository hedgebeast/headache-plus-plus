#include "order_manager.h"
#include "order.h"

#include <iterator>

void OrderManager::Add(int price, int qty, const std::string &order_id, bool is_sell) {
    // APPROACH 1: Add and then Sort
    
//    Order order_obj {price, qty, order_id, is_sell};
//    std::cout << "Order operator << : " << order_obj << std::endl;
//    std::vector<Order> order_vec {order_obj};

    if (qty > 0) {
    std::vector<Order> order_vec {Order {price, qty, order_id, is_sell}};   //Using default Move Constructor here for efficiency
//    display(order_vec);
    
//    std::cout << order_vec[0].price << std::endl;    
    std::copy(order_vec.begin(), order_vec.end(), std::back_inserter(orders_));
//    std::cout << "After inserting orders........" << std::endl;
//    display(orders_);


/* std::stable_sort: Sorts the elements in the range [first, last) in non-descending order
 * The order of equivalent elements is guaranteed to be preserved
 * Elements are compared using operator<
 */ 
    std::stable_sort(orders_.begin(), orders_.end());   //will sort it after every insert - added overloading operator<
//    std::cout << "After sorting orders........" << std::endl;
//    display(orders_);
    }
    else
        std::cout << "Order ID: " << order_id << " is invalid! Please submit an order with quantity more than 0!" << std::endl;
}

void OrderManager::Update(const std::string &order_id, int updated_open_qty) {
    
/* find searches for an element equal to value (using operator==) - added overloading operation==
 * The std::find function returns an iterator pointing to the ***first occurrence*** of the value in the range. 
 * If the value is not found, it returns the last iterator.
 */ 
    auto iter = std::find(orders_.begin(), orders_.end(), order_id);
    
    if (iter != orders_.end() && updated_open_qty >= 0){
        //    std::cout << order_id << std::endl;        
        // Calculate the position by subtracting the iterator from the beginning of the vector
        int position = std::distance(orders_.begin(), iter);
        
        std::cout << "\n[Updating for orderid: " << order_id << "]" << std::endl;
        std::cout << "Current open quantity is:" << orders_[position].open_qty << " for " << order_id << std::endl; 
        orders_[position].open_qty = updated_open_qty;
        
        std::cout << "Updated open quantity is:" << updated_open_qty << " for " << order_id << std::endl; 
        std::cout << "Updated order information: [" << orders_[position] << "]" << std::endl;
        
        if (orders_[position].open_qty == 0){
            std::cout << "Order with open quantity=0: [" << *iter << "] is DROPPED!" << std::endl << std::endl;;
            orders_.erase(iter);
        }
    } 
    else
        std::cerr << "Either Order ID cannot be found or updated open quantity cannot be NEGATIVE! Please try again." << std::endl << std::endl;
}

void OrderManager::PrintAllOrders() const {
    display(orders_);
//    std::for_each(orders_.begin(), orders_.end(), [](Order x){std::cout << x << std::endl;});

}