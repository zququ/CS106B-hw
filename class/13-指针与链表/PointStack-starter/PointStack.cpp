#include "PointStack.h"
#include "error.h"
#include "testing/SimpleTest.h"

PointStack::PointStack() {
    head = nullptr;
}

PointStack::~PointStack() {
    clear();
}

void PointStack::push(int x, int y) {
    Point *node = new Point(x, y);
    node->next = head;
    head = node;
}

Point PointStack::peek() const {
    if (isEmpty())
        error("error!");
    return *head;
}

Point PointStack::pop() {
    if (isEmpty())
        error("error!");
    Point *temp = head;
    head = head->next;
    Point result(temp->getX(), temp->getY());
    delete temp;
    return result;
}

void PointStack::clear() {
    if (!isEmpty()){
        Point *temp = head;
        while (head!=nullptr){
            head = head->next;
            delete temp;
        }
    }
}

int PointStack::size() const {
    int counter = 0;
    Point* temp = head;
    while (temp != nullptr){
        temp = temp-> next;
        ++ counter;
    }
    return counter;
}
bool PointStack::isEmpty() const {
    return head == nullptr;
}

std::string PointStack::toString() const {
    string result = "{";
    bool first = false;
    auto temp = head;
    while(temp != nullptr){
        if (first) {
            result += ", ";
        }
        first = true;
        temp = temp->next;
        result += temp->toString(); // Point
    }
    result += "}\n";
    return result;
}

// ************** 测试程序 ***************

PROVIDED_TEST("PointStack：构造器") {
    PointStack pts;
    EXPECT_EQUAL(pts.isEmpty(), true);
}

PROVIDED_TEST("PointStack：压栈") {
    PointStack pts;
    if (pts.isEmpty()) {
        pts.push(3, 5);
    }
    EXPECT_EQUAL(pts.peek(), {3, 5});
    EXPECT_EQUAL(pts.size(), 1);
}

PROVIDED_TEST("PointStack：出栈") {
    PointStack pts;
    if (pts.isEmpty()) {
        pts.push(3, 5);
        pts.push(2, 4);
    }
    pts.pop();
    EXPECT_EQUAL(pts.peek(), {3, 5});
}
