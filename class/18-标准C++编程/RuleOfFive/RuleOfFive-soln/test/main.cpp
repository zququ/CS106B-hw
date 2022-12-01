#include "mystring.h"
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

void passByRef(String& rsb) {
    cout << "String passed by reference:" << endl;
    cout << "    \"" << rsb << "\"" << endl;
}

void passByVal(String str) {
    cout << "String passed by value:" << endl;
    cout << "    \"" << str << "\"" << endl;
}

String returnByVal(String str) {
    cout << "String returned by value:" << endl;
    cout << "    \"" << str << "\"" << endl;
    return str;
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

    cout << "Case 6: 利用字符串赋值构造对象" << endl;
    String obj6;
    char temp[40];
    std::strcpy(temp, "Object 6");
    obj6 = temp;
    cout << "obj6: " << obj6 << endl << endl;

    cout << "Case 7: 移动临时对象" << endl;
    String obj7 = returnByVal(obj1);
    cout << "obj7: " << obj7 << endl << endl;
}

int main() {

    test();

    return 0;
}
