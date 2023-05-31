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
    virtual void say_hello() const {
        cout << "Hello - Base Class Object" << endl;
    }    
    
};

class Derived: public Base {
public:
//    virtual void say_hello() override {     //error: 'say_hello' marked 'override' but does not override any member functions
    virtual void say_hello() const override {
        cout << "Hello - Derived Class Object" << endl;
    }    
    
};

void greetings(const Base &obj){
    cout << "Greetings: ";
    obj.say_hello();
}

//----------------------------------------------------------------------------------------
//Abstract Classes as Interfaces
class I_Printable {
  friend ostream &operator<<(ostream &os, const I_Printable &obj);

public:
    virtual void print(ostream &os) const = 0;
};

ostream &operator<<(ostream &os, const I_Printable &obj){
    obj.print(os);
    return os;
}

class Account: public I_Printable {
public:
//    void withdraw(double amount){
    virtual void withdraw(double amount){
        cout << "In Account::withdraw" << endl;
    }
    virtual void print(ostream &os) const override {
        os << "Account Display";
    }
    
    //if a class has virtual functions, it must ALWAYS provide a public virtual destructor
    virtual ~Account(){
        cout << "Destructor in Account" << endl;
    }
};

class Checking: public Account{
public:
    virtual void withdraw(double amount) override{
        cout << "In Checking::withdraw" << endl;
    }
    
    virtual void print(ostream &os) const override {
        os << "Checking Display";
    }
    
    virtual ~Checking(){
        cout << "Destructor in Checking" << endl;
    }
};

class Savings: public Account{
public:
    virtual void withdraw(double amount) override{
        cout << "In Savings::withdraw" << endl;
    }
    
    virtual void print(ostream &os) const override {
        os << "Savings Display";
    }
    
    virtual ~Savings(){
        cout << "Destructor in Savings" << endl;
    }
};

class Trust: public Account{
public:
    virtual void withdraw(double amount) override{
        cout << "In Trust::withdraw" << endl;
    }
    
    virtual void print(ostream &os) const override {
        os << "Trust Display";
    }
    
    virtual ~Trust(){
        cout << "Destructor in Trust" << endl;
    }
};

void do_withdraw(Account &account, double amount){
    account.withdraw(amount);
}

class Dog: public I_Printable{
public:
    virtual void print(ostream &os) const override{
        os << "Woof Woof..?";
    }
};

void print(const I_Printable &obj){
    cout << obj << endl;
}

int main(){
    
    //Problem illustration: will still be statically binded to Base Class
    Base b;
    b.say_hello();
    
    Derived d;
    d.say_hello();
    
    greetings(b);
    greetings(d);
    
    
    Base *ptr = new Derived();
    ptr->say_hello();
    
    delete ptr;
    
    Derived *ptr1 = new Derived();
    ptr1->say_hello();
    
    delete ptr1;
    
    cout << "===================================== THANK U, NEXT =====================================\n";
    
    //Virtual functions are overridden functions that are bound dynamically
    //It allows us to treat all objects generally as objects of the Base class
    cout << "============= Pointers =============\n";
    Account *p1 = new Account();
    Account *p2 = new Savings();
    Account *p3 = new Checking();
    Account *p4 = new Trust();
    
    p1->withdraw(1000);
    p2->withdraw(1000);
    p3->withdraw(1000);
    p4->withdraw(1000);
    
    cout << "============= Clean Up =============\n";
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    
    
    cout << "============= Base Class References =============\n";
     Account a;
     Account &ref = a;
     ref.withdraw(1000);  //Account::withdraw
     
     Trust t;
     Account &ref1 = t;
     ref1.withdraw(1000); //Trust::withdraw
    
    Account a1;
    Savings a2;
    Checking a3;
    Trust a4;
    
    do_withdraw(a1, 1000);
    do_withdraw(a2, 2000);
    do_withdraw(a3, 3000);
    do_withdraw(a4, 4000);
    
    /***************************** Pure Virtual Functions and Abstract Classes! ****************************
     * Abstract Class cannot instantiate objects; used as base classes in inheritance hierarchies (Abstract Base Classes)
     * Contains at least one Pure Virtual Function
     * Pure Virtual Function is used to make a class abstract and it is specified with "=0" in its declaration
     * Typically do not provide implementations
     * Derived classes MUST override the base class (else it is also abstract)
     * 
    */ 
    
    Account *print1 = new Account();
    cout << *print1 << endl;
    
    Account *print2 = new Checking();
    cout << *print2 << endl;
    
    
    delete print1;
    delete print2;
    
    Dog *dog = new Dog();
    cout << *dog << endl;
    
    print(*dog);
    
    return 0;
}