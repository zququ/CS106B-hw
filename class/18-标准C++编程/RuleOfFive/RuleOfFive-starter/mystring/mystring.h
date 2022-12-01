// mystring.h -- String class definition
#ifndef STRING_H_
#define STRING_H_
#include <iostream>

class String {
private:
    char* str;               // pointer to string
    int len;                 // length of string
    static int num_strings;  // number of objects

public:
    String();               // default constructor
    String(const char* s);  // constructor
    ~String();              // destructor

    String(const String& other);             // copy constructor
    String& operator=(const String& other);  // copy assignment
    // TODO: Move Constructor
    // String(String&& other);                  // move constructor
    // TODO: Move Assignment
    // String& operator=(String&& other);       // move assignment

    // friend function
    friend std::ostream& operator<<(std::ostream& os, const String& st);
};
#endif
