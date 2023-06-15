#include "order_manager.h"
#include "order.h"
#include <iterator>


bool first_order_flag {false};

void OrderManager::Add(int price, int qty, const std::string& order_id, bool is_sell) {
    // APPROACH 2: Add while preserving the ordering
//    pq.emplace(price, qty, order_id, is_sell);    //don't use priority queue

/************************************************* TESTING std::lower_bound ********************************************************
    
//    std::vector<int> numbers = {10, 20, 30, 40, 50, 60};
    std::vector<int> numbers = {99,100};
    int valueToFind = 100;
    int valueToInsert = 100;
    
    auto reverse_iter = std::find(numbers.rbegin(), numbers.rend(), valueToFind).base();
    if (reverse_iter != numbers.end()+1) {
        std::cout << "I WAS HERE!!!!" << std::endl;
        numbers.insert(reverse_iter, valueToInsert);
    }

//    auto lowerBoundIter = std::lower_bound(numbers.begin(), numbers.end(), valueToFind);
//    auto upperBoundIter = std::upper_bound(numbers.begin(), numbers.end(), valueToFind);
//    
//    std::cout << *lowerBoundIter << std::endl;  //returns 0
//    std::cout << std::distance(numbers.begin(), lowerBoundIter) << std::endl;   //return 1
//    std::cout << "---------------------------------------\n";
//    std::cout << *upperBoundIter << std::endl;  //returns 0
//    std::cout << std::distance(numbers.begin(), upperBoundIter) << std::endl;   //return 1
//    
//    std::cout << *(numbers.end()) << std::endl;     //return 0
//    
//    if (lowerBoundIter != numbers.end() && *lowerBoundIter == valueToFind) {
//        std::cout << "Value " << valueToFind << " found at position " << std::distance(numbers.begin(), lowerBoundIter) << std::endl;
//        numbers.insert(lowerBoundIter+1, valueToFind);
//    } else {
//        std::cout << "Value " << valueToFind << " not found" << std::endl;
//        numbers.insert(lowerBoundIter, valueToFind);
//    }
    
    std::for_each(numbers.begin(), numbers.end(), [](int x){std::cout << x << " ";});
    
    std::exit(0);
    
*************************************************************************************************************************************/ 

    Order order_obj {price, qty, order_id, is_sell};
    std::vector<Order> order_vec {order_obj};
    
//    std::cout << "BEGINNING flag: " << first_order_flag << std::endl;
    //Don't insert first
//    std::copy(order_vec.begin(), order_vec.end(), std::back_inserter(orders_));       
    if (orders_.empty()){
        std::cout << "First Insert....\n";
        std::copy(order_vec.begin(), order_vec.end(), std::back_inserter(orders_)); 
        first_order_flag = true;
        
    }
    
    auto iter = std::lower_bound(orders_.begin(), orders_.end(), order_obj);
//    auto upperBoundIter = std::upper_bound(orders_.begin(), orders_.end(), order_obj);
        
//    if (orders_.size() >= 1 && (*iter).price == 0){
//        std::cout << "OH HI IT'S ME" << std::endl;
//        iter = std::upper_bound(orders_.begin(), orders_.end(), order_obj);
//    }
        
    
//    auto position = std::distance(orders_.begin(), iter);
    
    
//    std::cout << "flag: " << first_order_flag << std::endl;
    if (orders_.size() >= 1 && first_order_flag == false) {
        if (iter != orders_.end() && *iter == order_obj){
//            std::cout << "Same price: " << price << " found at position " << position << std::endl << std::endl;
            //iterate over the vector in reverse order and insert the value after finding the last occurrence
            auto reverse_iter = std::find(orders_.rbegin(), orders_.rend(), order_obj).base();
            
//            std::cout << "LOOK HERE: " << *reverse_iter << std::endl;  
//            std::cout << std::distance(orders_.begin(), reverse_iter) << std::endl;              
            if (reverse_iter != orders_.end() + 1) {
//                std::cout << "I CAME IN!!" << std::endl;
                orders_.insert(reverse_iter, order_vec.begin(), order_vec.end());
            }
        }
        else {
    //        std::copy(order_vec.begin(), order_vec.end(), std::back_inserter(orders_));  
//            std::cout << "Different Price: " << price << " is inserted at position " << position << std::endl << std::endl; 
            orders_.insert(iter, order_vec.begin(), order_vec.end());
        }
    }
    else {
        if (orders_.size() == 1){
            first_order_flag = false;
            std::cout << "There is only 1 entry on the order list. No need to sort!" << std::endl;
        }
        else
            std::cerr << "Order list is EMPTY! <Check that the 1st order entry is inserted correctly>" << std::endl;
    }

}

void OrderManager::Update(const std::string& order_id, int updated_open_qty) {
        
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
}

void OrderManager::PrintAllOrders() const {
    display(orders_);
    
}
