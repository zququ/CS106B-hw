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
    void find(const string &str);
    void replace(const string &str);

    string toString();

private:
    Node *head;
    Node *tail;
    Node *strToLink(const string &str);
    DISALLOW_COPYING_OF(LinkedString);
};

#endif
