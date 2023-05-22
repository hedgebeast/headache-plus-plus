#include "Account.h"

bool Account::deposit(double amount) {
    balance += amount; 
    return true;
};

bool Account::withdraw(double amount) {
    if (balance - amount < 0)
        return false;
        
    else {
        balance -= amount; 
        return true;
    }
};

void Account::set_balance(double balance){
    this->balance = balance; //disambiguate identifier use
}