#include "Savings_Account.h"

Savings_Account::Savings_Account(std::string name, double balance, double int_rate)
    : Account(name, balance), int_rate{int_rate} {
        
    }
    
//Savings_Account::Savings_Account()
//    : Savings_Account{"Unnamed", 0.0, 0.0}{
//    }

bool Savings_Account::deposit(double amount){
    amount += amount*int_rate/100;
    
//    Account::deposit(amount);
//    return true;
    return Account::deposit(amount);
}

std::ostream &operator<<(std::ostream &os, const Savings_Account &account){
    os << "[Account Holder: " << account.name << " Savings account balance: $" << account.balance << " Interest rate: " << account.int_rate << "%]";
    return os;
}