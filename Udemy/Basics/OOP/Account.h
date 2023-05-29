//#pragma once
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include <iostream>
#include <string>

/*
 * static: When applied to a member variable or function, the static keyword indicates that the variable 
 * or function belongs to the class itself, rather than an instance of the class. 
 * It means that the member is shared among all instances of the class, and you can access it without creating an object of the class.
 * -----------------------------------------------------------------------------------------------------------------------
 * constexpr: The constexpr keyword is used to declare that an expression or function can be evaluated at compile-time. 
 * It allows the compiler to compute the value of the expression or function during compilation rather than at runtime.
*/ 

class Account {
    friend std::ostream &operator<<(std::ostream &os, const Account &account);
    
private:
    static constexpr const char *def_name = "Unnamed Account";
    static constexpr double def_balance = 0.0;
    
    
    
protected:
    std::string name;
    double balance;
    
public:
//    Account();
    Account(std::string name = def_name, double balance = def_balance);
    bool deposit(double amount);
    bool withdraw(double amount);
    
    void set_balance(double);
    double get_balance() const;
    

};

#endif // _ACCOUNT_H_
