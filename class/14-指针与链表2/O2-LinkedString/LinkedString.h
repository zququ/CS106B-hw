#ifndef LINKEDSTRING_H
#define LINKEDSTRING_H
#include <string>

#include "testing/MemoryDiagnostics.h"
#include "testing/MemoryUtils.h"
using std::string;

struct Node {
    char ch;
    Node *next;
    TRACK_ALLOCATIONS_OF(Node);
};

class LinkedString {
public:
    LinkedString();
    LinkedString(const string &str);
    ~LinkedString();

    void clear();
    void append(const string &str);
    bool equal(const LinkedString &other);

    string toString();

private:
    // Task 1: O(N^2)
    Node *head;
    Node *strToLink(const string &str);
    DISALLOW_COPYING_OF(LinkedString);
};

#endif
