#include "PointStack.h"
#include "testing/SimpleTest.h"

PointStack::PointStack() {
    allocatedSize = INIT_SIZE;
    elems = new Point[allocatedSize];
//    elems2 = new char[allocatedSize];
    logicalSize = 0;
}

PointStack::~PointStack() {
    delete[] elems;
}

void PointStack::push(Point pt) {
    (void)pt;
    if (logicalSize == allocatedSize){
        expand();
    }
    elems[logicalSize] = pt; //pt give value to the current elems position (elems[logicalSize])
    logicalSize++;
}

Point PointStack::peek() const {
    if (size() == 0)
        error("Pointstack is empty, can't peek.");
    return elems[logicalSize - 1];
}

Point PointStack::pop() {
    if (size() == 0)
        error("Pointstack is empty, can't pop.");
    return elems[--logicalSize]; // firstly `logicalSize -1`, then give the value to the elems[] and return
}

int PointStack::size() const {
    return logicalSize;
}
bool PointStack::isEmpty() const {
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
    ostringstream sout;
    sout << *this;
    return sout.str();
}

bool PointStack::operator==(const PointStack &other){
    if (size()!=other.size()){
        return false;
    }
    Point *start1 = elems; // elems to replace the first place ([0]), if elems = new Point[]
    Point *end1 = elems + logicalSize;
    Point *start2 = other.elems;
    Point *end2 = elems + other.logicalSize;

    while (start1 != end1 && start2 != end2) {
        if (*start1 != *start2) {
            return false;
        }
//        start1 ++;
//        start2 ++;
        ++ start1;
        start2 ++;
    }
    return true;
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

PROVIDED_TEST("PointStack: ==") {
    PointStack pts1;
    PointStack pts2;

    if (pts1.isEmpty() && pts2.isEmpty()){
        pts1.push({3,5});
        pts1.push({1,2});
        pts1.push({2,4});
        pts2.push({3,5});
        pts2.push({1,2});
        pts2.push({2,4});
    }
    EXPECT(pts1 == pts2);
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
