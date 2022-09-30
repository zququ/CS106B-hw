#include "console.h"
#include "strlib.h"
#include <iostream>
using namespace std;

int main() {
    // string standard method
    string s = "Hello World";
    s += ", this is ";
    s.append(to_string(2022));
    char firstChar = s.at(0);
    char lastChar = s.at(s.length() - 1);
    cout << firstChar << lastChar << endl;
    if (s.find("e") != string::npos) {
        string first = s.substr(0, 5);
        string last = s.substr(7);
        cout << first << last << endl;
    }
    if (s == "Hello World") {
        cout << "Good job" << endl;
    }
    s.erase(5, 7);
    s.erase(6);
    s[5] = '!';
    cout << s << endl;

    // string stanford function
    int n = stringToInteger("42");
    cout << n << endl;
    string str = integerToString(42);
    cout << str << endl;

    // char
    cout << "Alphabets: ";
    for (int ch = 'A'; ch <= 'Z'; ch++) {
        cout << (char) ch;
    }
    cout << endl;
    cout << "'0' + 5 is " << '0' + 5 << endl;     // ???
    cout << "'Z' - 2 is " << 'Z' - 2 << endl;     // ???
    cout << "'a' - 'A' is " << 'a' - 'A' << endl; // ???

    // string literal
    // str = "Hello" + "World";

    return 0;
}
