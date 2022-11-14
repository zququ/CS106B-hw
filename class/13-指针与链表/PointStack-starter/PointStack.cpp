#include "PointStack.h"
#include "error.h"
#include "testing/SimpleTest.h"

PointStack::PointStack() {
    allocatedSize = INIT_SIZE;
    logicalSize = 0;
    elems = new Point[allocatedSize];
}

PointStack::~PointStack() {
    delete[] elems;
}

void PointStack::push(Point pt) {
    if (logicalSize == allocatedSize) {
        expand();
    }
    elems[logicalSize] = pt;
    logicalSize++;
}

Point PointStack::peek() const {
    if (size() == 0)
        error("error!");
    return elems[logicalSize - 1];
}

Point PointStack::pop() {
    if (size() == 0)
        error("error!");
    return elems[--logicalSize];
}

void PointStack::clear() {
    logicalSize = 0;
}

int PointStack::size() const {
    return logicalSize;
}
bool PointStack::isEmpty() const {
    return size() == 0;
}

void PointStack::expand() {
    // do sth
}

std::string PointStack::toString() const {
    string os = "{";
    bool first = false;
    for (int i = 0; i < logicalSize; i++) {
        if (first) {
            os += ", ";
        }
        first = true;
        os += elems[i].toString(); // Point
    }

    os += "}\n";
    return os;
}

// ************** 测试程序 ***************

PROVIDED_TEST("PointStack：构造器") {
    PointStack pts;
    EXPECT_EQUAL(pts.isEmpty(), true);
}

PROVIDED_TEST("PointStack：压栈") {
    PointStack pts;
    if (pts.isEmpty()) {
        pts.push({3, 5});
    }
    EXPECT_EQUAL(pts.peek(), {3, 5});
    EXPECT_EQUAL(pts.size(), 1);
}

PROVIDED_TEST("PointStack：出栈") {
    PointStack pts;
    if (pts.isEmpty()) {
        pts.push({3, 5});
        pts.push({2, 4});
    }
    pts.pop();
    EXPECT_EQUAL(pts.peek(), {3, 5});
}
