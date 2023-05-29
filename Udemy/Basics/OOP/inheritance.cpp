#include <iostream>
#include "Savings_Account.h"

using namespace std;

/*
 * Heritance: Process of creating new classes from existing classes (Reuse machanism)
 * Base class (Parent class/super class): The class being extended or inherited from 
 * Derived class (Child class/sub class): The class being created from the base class and will inherit attributed and operations from it
 * Public Inheritance: "Is-A relationship" - e.g. Savings_Account is a derived class of the Account base class
 *                                         -> No access to private members in Base class
 * Composition: "Has-A relationship" - e.g. Person "has a" Account 
 * 
 * The PROTECTED class member modifier 
 * (1) Accessible from the Base Class itself
 * (2) Accessible from the classes Derived from Base
 * (3) NOT accessible by objects of Base or Derived
*/

class Base {
//Note: friends of Base have access to all
public:
    int value, a{0};
    void display(){cout << a << ", " << b << ", " << c << endl;} //member method has access to all
    
    Base(): value{0} {
        cout << "Base no-args constructor" << endl;
    }
    Base(int x): value{x} {
        cout << "Base (int) overloaded constructor = " << value << endl;
    }
    
    Base(const Base &other)
        : value {other.value}{
            cout << "Base copy constructor" << endl;
        }
        
    Base &operator=(const Base &rhs){
        cout << "Base operator=" << endl;
        if(this == &rhs)
            return *this;
        
        value = rhs.value;
        
        return *this;
    }
    
    
    ~Base(){
        cout << "Base destructor" << endl;
    }

protected:
    int b {1};


private:
//    //Composition
//    string name;        //has-a name
//    Account account;    //has-an account
    int c {2};

};

/*
 * Derived class can directly invoke Base class methods
 * Derived class can override or redefine Base class methods
 * Very powerful in the contect of POLYMORPHISM
*/ 


class Derived: public Base {
//Note: friends of Derived have access to only what Derived has access to
//Copy/Move constructors and overloaded operator= are not inherited from the Base class
//using Base::Base;     //will inherit non-special constructors 

private:
    int doubled_value;
    
//a will be public; b will be protected; c will not be accessible
public:
    void access_base_members(){
        cout << "a = " << a << endl;   //OK
        cout << "b = " << b << endl;   //OK
//        cout << "c = " << c << endl;   //not accessible
        cout << "value = " << value << endl;
        }
        
    int get_doubled_value(){return doubled_value;}
    
    Derived(): Base(), doubled_value {0} {
        cout << "Derived no-args constructor" << endl;
    }
    Derived(int x): Base(x), doubled_value{x*2}{        //explicitly invoke the Base constructor
        cout << "Derived (int) overloaded constructor with doubled value = " << x*2 << endl;
    }
    
    Derived(const Derived &other)
    : Base(other), doubled_value {other.doubled_value}{
        cout << "Derived copy constructor" << endl;
    }
    
    Derived &operator=(const Derived &rhs){
        cout << "Derived operator=" << endl;
        
        if (this == &rhs)
            return *this;
            
        Base::operator=(rhs);
        doubled_value = rhs.doubled_value;
        
        return *this;
    }
    
    ~Derived(){cout << "Derived destructor" << endl;}
};


int main(){
    cout << "================== ACCESSING BASE MEMBER FROM BASE OBJECTS ==================" << endl;
    Base base;  //will inherit the non-special constructors
    
    cout << "Initially, value of a at base: " << base.a << endl;
    
    base.a = 100;
//    base.b = 200;   //Compiler Error  (Protected class member NOT accessible by objects of Base or Derived)
//    base.c = 300;   //Compiler Error
    
    cout << "Next, value of a at base: " << base.a << endl;
    
    cout << "================== ACCESSING BASE MEMBER FROM DERIVED OBJECTS ==================" << endl;
    Derived derived;
    
    derived.access_base_members();
    
    cout << "Initially, value of a at derived: " << derived.a << endl;
    
    derived.a = 500;
//    derived.b = 200;   //Compiler Error  (Protected class member NOT accessible by objects of Base or Derived)
//    derived.c = 300;   //Compiler Error

    cout << "Next, value of a at derived: " << derived.a << endl;
    cout << "Checking value of a at base again: " << base.a << endl;
    
    
    Base b;
//    Base b {100};
//    cout << b.value << endl;
    
//    Derived d;
    Derived d {1000};   //Overloaded constructor
    cout << "The base value is now initialize to: " << d.value << endl;
    cout << "The derived value is now initialize to: " << d.get_doubled_value() << endl;
    
    Derived d1 {d}; //Copy constructor
    d = d1;         //Copy assignment
    
    cout << "================== REDEFINING BASE CLASS METHODS (ACCOUNT CLASS) ==================" << endl;
    Account a0;
    cout << a0 << endl;
    
    Account a1 {"A1", 1000.0};
    cout << a1 << endl;
    
    a1.deposit(500.0);
    cout << a1 << endl;
    
    a1.withdraw(1000);
    cout << a1 << endl;
    
    a1.withdraw(1000);
    cout << a1 << endl;
    
    cout << "================== SAVINGS ACCOUNT CLASS ==================" << endl;
    Savings_Account s1{"s1", 1000, 5.0};
    cout << s1 << endl;
    
    s1.deposit(1000);
    cout << s1 << endl;
    
    s1.withdraw(2000);
    cout << s1 << endl;
    
    s1.withdraw(1000);
    cout << s1 << endl;
    
    return 0;
}