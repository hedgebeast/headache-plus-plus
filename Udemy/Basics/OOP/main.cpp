#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "Account.h" //remember to compile Account.cpp too (g++ -std=c++2a -o test main.cpp Account.cpp && ./test)

using namespace std;

/********************************************************************************************************************
 * Procedural programming: Typically a collection of functions and data is declared separately 
 * (functions need to know the structure of the data) - if structure of data changes many functions must be changed
 * 
 * What is Object-Oriented Programming (OOP)? 
 * (1) Classes and Objects - allows developers to think at a higher level of ABSTRACTION
 * (2) Encapsulation - objects contain data and operations that work on that data (Abstract Data Type)
 * (3) Classes are user-defined data-type
 * (4) Objects are created from a class and represents a specific instance of a class
 * 
 ********************************************************************************************************************/ 

class Player {
public:
    //Attributes
    string name {"Player"};
    int health {100};
    int exp {0};
    
    
    //Methods
    void talk(string str){cout << "It's me HI, I'm " << name << " it's me! " << str << endl;}
    bool is_dead();
};

//MOVE CLASS DECLARATION TO HEADER FILE
//class Account {
//public:
//    string name {"Account"};
//    double balance {0.0};
//  
////    bool deposit(double bal) {balance += bal; return 1;}
//    bool deposit(double);
//    bool withdraw(double);
//};

//Member methods can be implemented outside of the Class declaration (MOVE TO ACCOUNT.CPP FILE)
//Need to use Class_name::method_name
//bool Account::deposit(double amount) {
//    balance += amount; 
//    return true;
//};
//
//bool Account::withdraw(double amount) {
//    if (balance - amount < 0)
//        return false;
//        
//    else {
//        balance -= amount; 
//        return true;
//    }
//};


int main(){
    cout << "Welcome to Vitamin C++!" << endl;
    
    Player dumbo;
    Player limbo;
    
    Player players[] {dumbo, limbo};
    
    vector<Player> player_vec {dumbo};
    player_vec.push_back(limbo);
    
    //Example: Declaring enemy as a pointer to a player object and creating that object dynamically on the heap using new
//    Player *enemy {nullptr};
//    enemy = new Player;

    //OR Player *enemy = new Player();
    Player *enemy = new Player; //Player() or just Player -> both works
    
    enemy->name = "Enemy";
    enemy->health = 100;
    enemy->exp = 15;
    enemy->talk("You are so dead~");
    
    delete enemy;
    
    cout << "------------------------------- ACCESSING CLASS MEMBERS -------------------------------" << endl;
    
    dumbo.name = "Dumbo Bodoh";
    dumbo.health = 90;
    dumbo.exp = 2;
    
    cout << "It's me Hi, I'm " << dumbo.name << " it's me!" << endl;
    dumbo.talk("lol dedddd");
    
    
    Account dumbo_account;
    Account limbo_account;
    
    cout << "Poor Dumbo has $" << dumbo_account.balance << " in his bank account :(" << endl;
    double bal {1.00};
    cout << "Dumbo shall deposit $" << bal << " and become financially free!" << endl;
//    cout << "1==1 (True) is: " << (1==1) << " and 1==0 (False) is: " << (1==0) << endl; 
//    cout << boolalpha;
    cout<< "Deposit is " << dumbo_account.deposit(bal) << endl;
    cout << "Now rich Dumbo has $" << dumbo_account.balance << " in his bank account :D" << endl;
    
    
    //If we have a pointer to an object (member of pointer operator)
    // (1) Dereference the pointer then use the dot operator
    // (2) or use the member of pointer operator (arrow operator)
    
    Account *bimbo_account = new Account();
    
    bimbo_account->set_balance(129.50);
    
    cout << fixed << setprecision(2);
    cout << "Checking Bimbo's account balance: $" << (*bimbo_account).balance << endl;
//    cout << (*bimbo_account).deposit(1000.00);
    
    //OR
//    bimbo_account->balance;
//    bimbo_account->deposit(1000.00);
    
    delete bimbo_account;
    
	return 0;
}
