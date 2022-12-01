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

    // TODO: Copy Constructor
    // String(const String &other);
    // TODO: Copy Assignment
    // String &operator=(const String &other);

    // friend function
    friend std::ostream& operator<<(std::ostream& os, const String& st);
};
#endif
