#include <iostream>

#include <vector>
#include <list>
#include <algorithm>    //STL algorithms
#include <numeric>      //to use the accumulate algo
#include <cctype>

#include "Item.h"

/* A library of powerful, resuable, adaptable, generic classes and functions implemented using C++ templates. 
 * Assortment of commonly used containers (known time and size complexity)
 * 
 * 3 Main Elements of the STL
 * (1) Containers: Collections of objects or primitive types (i.e. array, vector, deque, stack, set, map, etc)
 *      -> Sequence Containers
 *          -> Array
 *          -> Vector
 *          -> List
 *          -> Forward_list
 *          -> Deque
 *      -> Associative Containers
 *          -> Set/Multi-set    (no duplicates)
 *          -> Map/Multi-map    (like a dictionary)
 *      -> Container Adapters
 *          -> Stack
 *          -> Queue
 *          -> Priority Queue
 * (2) Algorithms: Functions for processing sequences of elements from containers (i.e. find, max, count, accumulate, sort, etc)
 *      -> Non-modifying
 *      -> Modifying
 *      (All STL Algorithms expect iterators as arguments)
 * (3) Iterators: Generate sequences of element from containers (i.e. forwardm reversem by value, by reference, constant, etc)
 *      -> Input iterator - from the container to the program
 *      -> Output iterator - from the program to the container
 *      -> Forward iterators - navigate one item at a time in one direction
 *      -> Bi-directional iterators - navigate one item at a time both directions
 *      -> Random access iterators - directly access a container item
*/ 

template <typename T>   //need to tell c++ that this is a template (may also use class instead of typename)
    T max(T a, T b){
        return (a > b) ? a : b;     //must be careful of the operator used in template
    }

//template function to display ANY vector
template <typename T>
    void display(const std::vector<T> &vec) {
        std::cout << "[ ";
        for (const auto &elem:vec)
            std::cout << elem << " ";
        std::cout << "]" << std::endl;
    }

//Use for_each and a lambda expression to display vector elements
void display2(const std::vector<int> &vec){
    std::cout << "[ ";
    std::for_each(vec.begin(), vec.end(), [](int x){std::cout << x << " ";});
    std::cout << "]" << std::endl;
}    


struct Person {
    friend std::ostream &operator<<(std::ostream &os, const Person &p);
//private:
//    std::string name;
//    int age; 
    
public:
    std::string name;
    int age;

    Person() = default;     //default construction that compiler will create
    Person(std::string name, int age)
        : name{name}, age{age} {}
    
    bool operator>(const Person &rhs) const {       //can alter field to compare here when using priority queue
        return this->age > rhs.age;
    }
    
    bool operator==(const Person&rhs) const{
        return (this->name == rhs.name && this->age == rhs.age);
    }
};

std::ostream &operator<<(std::ostream &os, const Person &p){
    os << p.name << ": " << p.age;
    return os;
}

int main(){
    std::cout << "Hallo Hallo Citizens of C++" << std::endl;
    
    Person p1 {"Loki", 1};
    Person p2 {"Leon" , 30};
    
    Person p3 = max(p1,p2);
    std::cout << p3.name << " is older" << std::endl;
    
    
    std::vector<int> vec {1,5,3};
    std::sort(vec.begin(), vec.end());  //iterator begin and end methods
    
    std::cout << "testing my template display function" << std::endl;
    display(vec);
    std::cout << "testing my display2 function" << std::endl;
    display2(vec);
    
    std::vector<int> vec1 (10, 100);    //ten 100s in the vector
    display(vec1);
    std::vector<int> vec2 {10, 100};    //[10, 100]
    display(vec2);
    
    //Erasing some elements
    std::vector<int> test_drop {1,2,3,4,5,6,7,8,9,10};
    display(test_drop);
    test_drop.erase(test_drop.begin(), test_drop.begin()+2);
    display(test_drop);
    
    //std::back_inserter constructs a back-insert iterator that inserts new elements at the end of the container it's applied to
    std::copy(test_drop.begin(), test_drop.end(), std::back_inserter(vec2)); //test_drop added to the back of vec2
    display(vec2);
    std::cout << std::endl;
    
//    std::copy_if(test_drop.begin(), test_drop.end(), std::back_inserter(vec2), [](int x){return x%2 == 0;});

    std::cout << "========= Element-wise multiplication =========" << std::endl;
    std::vector<int> v1 {1,2,3,4,5};
    std::vector<int> v2 {10,20,30,40,50};
    std::vector<int> v3;
    std::vector<int> v4;
    
    std::transform(v1.begin(), v1.end(), v2.begin(), std::back_inserter(v3), [](int x, int y){return x*y;});
    display(v3);
//    display(v1*v2);   //ERROR

    auto itt = std::find(v1.begin(), v1.end(), 5);
    if (itt != v1.end()){
        std::cout << "========= INSERTING..... =========" << std::endl;
        v1.insert(itt, v2.begin(), v2.end());
    }
    else
        std::cout << "Sorry, 5 not found." << std::endl;
        
    display(v1);
    
    for (auto elem: vec)
        std::cout << elem << std::endl;
        
    std::cout << "TRYING ITERATOR!" << std::endl;    
    std::vector<int>::iterator it = vec.begin();    //pointing to the 1st element
    while (it != vec.end()){
        std::cout << *it << " " ;
        ++it;
    }

//    for (auto it = vec.begin(); it != vec.end(); it++){
//        std::cout << *it << " " ;
//    }
    
    std::cout << std::endl;
        
    int sum{};
    sum = std::accumulate(vec.begin(), vec.end(), 0);    //if wanna sum float, the last argument needs to be 0.0
    std::cout << sum << std::endl;
    
    
    std::cout << max<int>(5, 55) << std::endl;    //can use almost any type
    
    std::cout << "=================================== CLASS TEMPLATE NEXT ===================================\n";
    
    Item<int> item1 {"Loki", 1000};
    std::cout << item1.get_name() << " " << item1.get_value() << std::endl;
    
    
    Item<Item<std::string>> item2 {"Leon", {"C++", "NOOB :("}};
    std::cout << item2.get_name() << " is a " << item2.get_value().get_name() << " " << item2.get_value().get_value() << std::endl;
    
    My_Pair<std::string, int> x1 {"Leon", 999};
    My_Pair<int, double> x2 {123, 942.123};
    
    std::cout << x1.first << ", " << x1.second << std::endl;
    std::cout << x2.first << ", " << x2.second << std::endl;
    
	return 0;
}
