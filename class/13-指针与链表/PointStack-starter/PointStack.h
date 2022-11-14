#ifndef POINTSTACK_H
#define POINTSTACK_H
#include "Point.h"
#include <iostream>
using namespace std;

class PointStack {
public:
    PointStack();
    ~PointStack();

    void push(Point pt);
    Point peek() const;
    Point pop();
    void clear();

    int size() const;
    bool isEmpty() const;
    std::string toString() const;

private:
    static const int INIT_SIZE = 8;

    Point *elems;
    int allocatedSize;
    int logicalSize;

    void expand();
};

#endif
