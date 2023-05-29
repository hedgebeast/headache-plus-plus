#include "Account.h"


//Account::Account()
//    : Account{0.0} {}; //delegating constructor

Account::Account(std::string name, double balance)
    : name{name}, balance{balance} {};



bool Account::deposit(double amount) {
    balance += amount; 
    return true;
};

bool Account::withdraw(double amount) {
    if (balance - amount < 0) {
        std::cout << "Insufficient funds" << std::endl;
        return false;
    }
        
        
    else {
        balance -= amount; 
        return true;
    }
};

void Account::set_balance(double balance){
    this->balance = balance; //disambiguate identifier use
}

double Account::get_balance() const {
    return balance;
}

std::ostream &operator<<(std::ostream &os, const Account &account){
    os << "[Account holder: " << account.name << " Account balance: $" << account.balance << "%]";
    return os;
}