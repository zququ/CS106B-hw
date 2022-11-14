/******************************************************
 * File: BankAccount.h
 *
 * A class representing a bank account, which stores the
 * account holder's name and current amount balance.
 */
#pragma once
#include <string>
using std::string;

class BankAccount {
public:
    BankAccount(string name, double amount);
    void deposit(double amount);
    void withdraw(double amount);
    void transfer(double amount, BankAccount &recipient);

    double getAmount() const;
    string getName() const;

private:
    string _name;
    double _amount;
};
