#ifndef _ORDER_MANAGER_H_
#define _ORDER_MANAGER_H_
#include "order.h"

#include <algorithm>
#include <vector>
//#include <queue>


/* OrderManager is a class which manages all the open orders, i.e. order with open_qty > 0. 
 * The order manager should keep the records in a std::vector in a sorted manner:
 * (1) orders with lower prices should be placed before orders with higher prices
 * (2) orders with the same price should be sorted according to the order of insertion, i.e. FIFO order
 */

//template function to display any vector
template <typename T>
void display(const std::vector<T> &vec) {
    for (const auto &elem:vec)
        std::cout << elem << std::endl;
}

//template <typename T>
//void display(std::priority_queue<T> pq){
//    while (!pq.empty()){
//        T elem = pq.top();
//        pq.pop();
//        std::cout << elem << std::endl;
//    }
//}

template<class ForwardIt, class T>
bool binary_search(ForwardIt first, ForwardIt last, const T &value)
{
    first = std::lower_bound(first, last, value);
    return (!(first == last) and !(value < *first));
}


class OrderManager {
public:
    // add a new record to the order manager
    void Add(int price, int qty, const std::string& order_id, bool is_sell);

    // update the open_qty for an existing order record and delete the record if updated_open_qty== 0
    void Update(const std::string& order_id, int updated_open_qty);

    // print all orders following the order specified, i.e. 
    // - from lower prices to high prices 
    // - following FIFO if same price
    void PrintAllOrders() const;
    

private:
    std::vector<Order> orders_;
    
//    std::priority_queue<Order> pq; (Idea: wanted to use priority queue for the auto-sorting then pop entries into the front of a vector)
};

#endif // _ORDER_MANAGER_H_