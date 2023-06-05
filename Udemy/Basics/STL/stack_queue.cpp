#include <iostream>
#include <stack>
#include <queue>

#include <vector>

/* std::stack (implemented as an adapter over other STL container)
 * Last-in First-out (LIFO) data structure - all operations over on one end of the stack (top)
 * 
 * std::queue (can be implemented as a list or deque)
 * First-in First-out (FIFI) data structure - elements are pushed at the back and popped from the front
 * 
 * std::priority_queue - allows insertions and removal of elements in order from the front of the container
 * Elements are stored internally as a VECTOR by default
 * Elements are inserted in PRIORITY oder (largest value will always be at the front)
 * (1) push - insert an element into SORTED order
 * (2) pop - removes the TOP element (greatest)
 * (3) top - access the top element (greatetst
 * (4) empty - is the queue empty?
 * (5) size - number of elements in the queue
 */ 

template <typename T>
void display(std::stack<T,std::vector<int>> s){
    std::cout << "[ ";
    while (!s.empty()){
        T elem = s.top();
        s.pop();
        std::cout << elem << " ";
    }
    std::cout << "]" << std::endl;
}

template <typename T>
void display(std::queue<T> q){
    std::cout << "[ ";
    while (!q.empty()){
        T elem = q.front();
        q.pop();
        std::cout << elem << " ";
    }
    std::cout << "]" << std::endl;
}

template <typename T>
void display(std::priority_queue<T> pq){
    std::cout << "[ ";
    while (!pq.empty()){
        T elem = pq.top();
        pq.pop();
        std::cout << elem << " ";
    }
    std::cout << "]" << std::endl;
}

int main(){
    
    std::stack<int> s;  //by default it will be deque
    std::stack<int, std::vector<int>> s1;   //vector
    
    s1.push(10);
    s1.push(20);
    s1.push(30);
    
    std::cout << s1.top() << std::endl;
    display(s1);
    std::cout << s1.top() << std::endl;
    
    std::queue<int> q;  //by default is deque too
    
    q.push(100);
    q.push(200);
    q.push(300);
    
    std::cout << q.front() << std::endl;
    std::cout << q.back() << std::endl;
    display(q);
    
    q.pop();    //remove 100 (FIFO)
    display(q);
    
    std::cout << "================== Excuse me. PRIORITY Queue Please! ==================" << std::endl;
    std::priority_queue<int> pq;    //vector 
    
    pq.push(10);
    pq.push(20);
    pq.push(3);
    pq.push(4);
    
    //PQ is implemented as a max-heap by default, where the element with the highest priority appears at the top.
    display(pq);
    
    std::cout << pq.top() << std::endl;  //20 (largest)
    pq.pop();
    display(pq);
    pq.push(999);
    display(pq);
    

    return 0;
}