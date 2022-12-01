#include "mystring.h"
#include <iostream>
using std::cout;
using std::endl;

void passByRef(String& rsb) {
    cout << "String passed by reference:" << endl;
    cout << "    \"" << rsb << "\"" << endl;
}

void passByVal(String sb) {
    cout << "String passed by value:" << endl;
    cout << "    \"" << sb << "\"" << endl;
}

void test() {
    cout << "Case 1: 利用字符串构造对象" << endl;
    String obj1("Object 1");
    String obj2("Object 2");
    String obj3("Object 3");
    cout << "obj1: " << obj1 << endl;
    cout << "obj2: " << obj2 << endl;
    cout << "obj3: " << obj3 << endl << endl;

    cout << "Case 2: 引用传递对象" << endl;
    passByRef(obj1);
    cout << obj1 << endl << endl;

    cout << "Case 3: 传值传递对象" << endl;
    passByVal(obj2);
    cout << obj2 << endl << endl;

    cout << "Case 4: 用现有对象构造对象" << endl;
    String obj4 = obj3;
    cout << "obj4: " << obj4 << endl << endl;

    cout << "Case 5: 把现有对象赋值给另一个对象" << endl;
    String obj5;
    obj5 = obj1;
    cout << "obj5: " << obj5 << endl << endl;
}

int main() {

    test();

    return 0;
}
