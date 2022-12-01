// mystring.cpp -- String class methods
#include "mystring.h"

#include <cstring>
using std::cout;
using std::endl;

// initializing static class member
int String::num_strings = 0;

// class methods

// TODO: Move Constructor
// String::String(String&& other)  // move constructor
//{}
// TODO: Move Assignment
// String& String::operator=(String&& other)  // move assignment
//{}

String::String(const String& other)  // copy constructor
{
    len = other.len;
    str = new char[len + 1];
    std::memcpy(str, other.str, len + 1);
    num_strings++;
    cout << num_strings << ": \"" << str << "\" created" << endl;
    cout << "=== Copy Constructor finished ===" << endl;
}

String& String::operator=(const String& other)  // copy assignment
{
    if (this != &other) {
        delete[] str;
        len = other.len;
        str = new char[len + 1];
        std::memcpy(str, other.str, len + 1);
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

String::String(const char* s)  // construct String from C string
{
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
