#include <iostream>

using namespace std;

/************************** WHAT IS POLYMORPHISM? **************************
 * (1) Compile-time / Early Binding / Static Binding
 * (2) Run-time (Function Overriding) / Late Binding / Dynamic Binding
 *      - Being able to assign different meanings to the same function at run-time
 *      - Allows us to program more abstractly (Let C++ figure out which function to call at run-time) :O
 * 
 * Run-time Polymorphism is achieved via: (1) Inheritance (2) Base class pointers/references (3) Virtual Functions
 * 
*/ 

class Base {
public:
    void say_hello() const {
        cout << "Hello - Base Class Object" << endl;
    }    
    
};

class Derived: public Base {
public:
    void say_hello() const {
        cout << "Hello - Derived Class Object" << endl;
    }    
    
};

void greetings(const Base &obj){
    cout << "Greetings: ";
    obj.say_hello();
}

int main(){
    
    Base b;
    b.say_hello();
    
    Derived d;
    d.say_hello();
    
    greetings(b);
    greetings(d);
    
    
    return 0;
}