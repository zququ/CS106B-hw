// mystring.cpp -- String class methods
#include "mystring.h"

#include <cstring>
using std::cout;
using std::endl;

// initializing static class member
int String::num_strings = 0;

// class methods

// TODO: Copy Constructor
// 用另一个对象数据构造新对象
String::String(const String& other) {
    len = other.len;                       // set size
    str = new char[len + 1];               // allot storage
    std::memcpy(str, other.str, len + 1);  // initialize pointer
    num_strings++;                         // set object count
    cout << num_strings << ": \"" << str << "\" created" << endl;
    cout << "=== Copy Constructor finished ===" << endl;
}

// TODO: Copy Assignment
// 1. 现有对象 -> 返回值引用
// 2. 自我复制
// 3. 现有动态内存
// 4. 用另一个对象数据替换现有数据
String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] str;                          // free old string
        len = other.len;                       // set size
        str = new char[len + 1];               // allot new storage
        std::memcpy(str, other.str, len + 1);  // initialize pointer
        cout << "=== Copy Assignment finished ===" << endl;
    }

    return *this;
}

String::String()  // default constructor
{
    len = 0;
    str = new char[1];
    str[0] = '\0';
    num_strings++;
    cout << num_strings << ": \"" << str << "\" created" << endl;
    cout << "=== Default Constructor finished ===" << endl;
}

// construct String from C string
String::String(const char* s) {
    len = std::strlen(s);          // set size
    str = new char[len + 1];       // allot storage
    std::memcpy(str, s, len + 1);  // initialize pointer
    num_strings++;                 // set object count
    cout << num_strings << ": \"" << str << "\" created" << endl;
    cout << "=== Constructor with params finished ===" << endl;
}

String::~String()  // destructor
{
    cout << "\"" << str << "\" deleted, ";   // FYI
    --num_strings;                           // required
    cout << num_strings << " left" << endl;  // FYI
    delete[] str;                            // required
    cout << "=== Destructor finished ===" << endl;
}

std::ostream& operator<<(std::ostream& os, const String& st) {
    os << st.str;
    return os;
}
