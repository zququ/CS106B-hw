#ifndef POINTSTACK_H
#define POINTSTACK_H
#include "Point.h"
#include <iostream>
using namespace std;

class PointStack {
public:
    PointStack();
    ~PointStack();

    void push(int x, int y);
    Point peek() const;
    Point pop();
    void clear();

    int size() const;
    bool isEmpty() const;
    string toString() const;

private:
    Point* head;
};

#endif
