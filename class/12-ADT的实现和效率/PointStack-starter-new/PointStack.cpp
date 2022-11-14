#include "PointStack.h"
#include "testing/SimpleTest.h"

PointStack::PointStack() {
}

PointStack::~PointStack() {
}

void PointStack::push(Point pt) {
    (void)pt;
}

Point PointStack::peek() const {
    return {0, 0};
}

Point PointStack::pop() {
    return {0, 0};
}

int PointStack::size() const {
    return 0;
}
bool PointStack::isEmpty() const {
    return false;
}

void PointStack::expand() {
    // do sth
}

ostream &operator<<(ostream &os, const PointStack &pts) {
    (void)pts;
    return os;
}

std::string PointStack::toString() const {
    return "";
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
