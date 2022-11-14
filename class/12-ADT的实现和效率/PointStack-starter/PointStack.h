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

    int size() const;
    bool isEmpty() const;

    std::string toString() const;
    friend ostream &operator<<(ostream &os, const PointStack &pts);
    bool operator==(const PointStack &other);

private:
    static const int INIT_SIZE = 8;

    Point *elems;
//    char *elems2;
    int allocatedSize;
    int logicalSize;

    void expand();
};

#endif
