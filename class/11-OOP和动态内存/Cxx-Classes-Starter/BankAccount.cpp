#include "BankAccount.h"
#include "console.h"
#include "error.h"
#include "testing/SimpleTest.h"
using namespace std;

BankAccount::BankAccount(string name, double amount) {
    // 开户金额小于 0
    if (amount < 0)
        error("开户金额小于 0");
    _name = name;
    _amount = amount;
}

void BankAccount::deposit(double amount) {
    // 取款金额小于 0
    if (amount < 0)
        error("取款金额小于 0");
    _amount += amount;
}

void BankAccount::withdraw(double amount) {
    // 如果取款金额小于 0
    if (amount < 0)
        error("取款金额小于 0");
    // 如果取款金额大于余额
    if (amount > amount)
        error("取款金额大于余额");
    _amount -= amount;
}

void BankAccount::transfer(double amount, BankAccount recipient) {
    withdraw(amount);
    recipient.deposit(amount);
}

double BankAccount::getAmount() const {
    return _amount;
}

string BankAccount::getName() const {
    return _name;
}

// ************** 测试程序 ***************

PROVIDED_TEST("BankAccount：开户金额大于 0") {
    EXPECT_NO_ERROR([](void) {
        BankAccount jenny("Jenny", 100);
        cout << jenny.getName() << ":" << jenny.getAmount() << endl;
    }());
}

PROVIDED_TEST("BankAccount：开户金额小于 0") {
    EXPECT_ERROR([](void) {
        BankAccount jenny("Jenny", -100);
        cout << jenny.getName() << ":" << jenny.getAmount() << endl;
    }());
}

PROVIDED_TEST("BankAccount：测试成员函数") {
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
