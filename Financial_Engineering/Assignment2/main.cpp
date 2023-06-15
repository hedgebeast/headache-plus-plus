#include <iostream>

#include "order_manager.h"

int main() {
    OrderManager order_manager;

//    order_manager.Add(99, 4, "AAA", true);
//    order_manager.Add(100, 2, "BBB", true);
    
    order_manager.Add(100, 2, "o1", true);
    order_manager.Add(99, 1, "o2", true);
    order_manager.Add(100, 3, "o3", true);
    order_manager.Add(101, 4, "o4", true);
    
//    order_manager.Add(99, 1, "CCC", true);
//    order_manager.Add(99, 3, "DDD", true);
//    order_manager.Add(50, 4, "o5", true);
//    order_manager.Add(50, 0, "o6", true);

    std::cout << "Step 1" << std::endl;
    std::cout << "[Print after 1st round of adding...]" << std::endl;
    order_manager.PrintAllOrders();

    order_manager.Update("o3", 1);
    order_manager.Update("o2", 0);
////    order_manager.Update("o5", -1);
    std::cout << "[Print after 1st round of updating...]" << std::endl;
    order_manager.PrintAllOrders();

    
    order_manager.Add(98, 5, "o5", false);
    order_manager.Add(101, 1, "o6", true);
    order_manager.Add(100, 2, "o7", true);
    std::cout << "\nStep 2" << std::endl;
    std::cout << "[Print after 2nd round of adding...]" << std::endl;
    order_manager.PrintAllOrders();
    return 0;
}