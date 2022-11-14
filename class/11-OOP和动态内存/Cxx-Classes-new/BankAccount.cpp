#include "BankAccount.h"
#include "error.h"
#include "testing/SimpleTest.h"

using std::string;

BankAccount::BankAccount(string name, double amount) {
    this->name = name;
    this->amount= amount;
}

void BankAccount::deposit(double amount){
    if (amount < 0){
        error("321 ");
    }
    this->amount += amount;
}

double BankAccount::getAmount() const{
    return this->amount;
}

void BankAccount::withdraw(double amount){
    if (amount > this->amount){
        error("123 ");
    }
    this->amount -= amount;
}

void BankAccount::transfer(double amount, BankAccount &recipient){
    withdraw(amount);
    recipient.deposit(amount);
}

string BankAccount::getName() const{
    return this->name;
}

PROVIDED_TEST("1"){
    BankAccount jenny("Jenny", 100);
    BankAccount kylie("Kylie", 1000);

    jenny.deposit(500);
    EXPECT_EQUAL(jenny.getAmount(), 600);

    kylie.withdraw(900);
    EXPECT_EQUAL(kylie.getAmount(), 100);

    jenny.transfer(20, kylie);
    EXPECT_EQUAL(jenny.getAmount(), 580);
    EXPECT_EQUAL(kylie.getAmount(), 120);
}
