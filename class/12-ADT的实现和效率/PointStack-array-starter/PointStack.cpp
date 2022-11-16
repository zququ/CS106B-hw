#include "PointStack.h"
#include "testing/SimpleTest.h"

PointStack::PointStack() {
    allocatedSize = INIT_SIZE;
    elems = new Point[allocatedSize];
    logicalSize = 0;
}

PointStack::~PointStack() {
    delete[] elems;
}

void PointStack::push(Point pt) {
    (void)pt;

    if (logicalSize == allocatedSize) {
        expand();
    }

    elems[logicalSize] = pt;
}

Point PointStack::peek() const {
    if (size() == 0){
        error("");
    }
    return elems[logicalSize - 1];
}

Point PointStack::pop() {
    if (size() == 0){
        error("");
    }
    return elems[--logicalSize];
}

int PointStack::size() const {
    return logicalSize;
}
bool PointStack::isEmpty() const {
//    if (size() == 0) {
//        return true;
//    }
//    return false;
    return size()==0;
}

void PointStack::expand() {
    // do sth
}

ostream &operator<<(ostream &os, const PointStack &pts) {
    (void)pts;

    os << "{";
    bool first = false;
    for (int i = 0; i < pts.logicalSize; i++){
        if (first) {
            os << ",";
        }
        first = true;
        os << pts.elems[i];
    }
    os << "}";
    return os;
}

std::string PointStack::toString() const {
    ostringstream cout;
    cout << *this;
    return cout.str();
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

// void createStack(int num) {
//     PointStack pts;
//     for (int i = 0; i < num; i++) {
//         pts.push({i, i});
//     }
// }

//PROVIDED_TEST("动态内存管理") {
//    for (int size = 100; size < 1000; size *= 2)
//        TIME_OPERATION(size, createStack(size));
//}
