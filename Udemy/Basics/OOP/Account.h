//#pragma once
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include <iostream>
#include <string>

class Account {
public:
    std::string name {"Account"};
    double balance {0.0};
  
    bool deposit(double amount);
    bool withdraw(double amount);
    
    void set_balance(double);
};

#endif // _ACCOUNT_H_
