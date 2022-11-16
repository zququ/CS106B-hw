#include "PointStack.h"
#include "testing/SimpleTest.h"

PointStack::PointStack() {
    head = nullptr;
}

PROVIDED_TEST("PointStack：构造器") {
    PointStack pts;
    EXPECT_EQUAL(pts.isEmpty(), true);
}

PointStack::~PointStack() {
    clear();
}

void PointStack::push(int x, int y) {
    Point *node = new Point(x, y);
    node->next = head;
    head = node;
}

PROVIDED_TEST("PointStack：压入 100 个 Point 对象") {
    PointStack pts;
    for (int i = 0; i < 100; i++)
        pts.push(i, i);
}

Point PointStack::peek() const {
    if (isEmpty()) {
        error("当前为空栈，没有元素");
    }
    return *head;
}

PROVIDED_TEST("PointStack：查询栈顶") {
    PointStack pts;
    EXPECT_ERROR(pts.peek());
    pts.push(3, 5);
    EXPECT_EQUAL(pts.peek(), {3, 5});
    pts.push(2, 4);
    EXPECT_EQUAL(pts.peek(), {2, 4});
    for (int i = 0; i < 100; i++) {
        pts.push(i, i);
        EXPECT_EQUAL(pts.peek(), {i, i});
    }
}

Point PointStack::pop() {
    if (isEmpty()) {
        error("当前为空栈，没有元素");
    }
    Point *temp = head;
    head = head->next;

    Point result(temp->getX(), temp->getY());
    delete temp;
    return result;
}

PROVIDED_TEST("PointStack：出栈并释放动态内存") {
    PointStack pts;
    pts.push(3, 5);
    pts.push(2, 4);
    auto pt1 = pts.pop();
    EXPECT_EQUAL(pt1, {2, 4});
    auto pt2 = pts.pop();
    EXPECT_EQUAL(pt2, {3, 5});
}

void PointStack::clear() {
    if (!isEmpty()) {
        while (head != nullptr) {
            Point *temp = head;
            head = head->next;
            delete temp;
        }
    }
}

PROVIDED_TEST("PointStack：清空栈") {
    PointStack pts;
    pts.push(3, 5);
    pts.push(2, 4);
    pts.clear();
    EXPECT_EQUAL(pts.size(), 0);
}

int PointStack::size() const {
    int total = 0;
    auto temp = head;
    while (temp != nullptr) {
        temp = temp->next;
        ++total;
    }
    return total;
}

bool PointStack::isEmpty() const {
    return head == nullptr;
}

PROVIDED_TEST("PointStack：检测大小") {
    PointStack pts;
    EXPECT(pts.isEmpty());
    pts.push(3, 5);
    pts.push(2, 4);
    EXPECT_EQUAL(pts.size(), 2);
}

string PointStack::toString() const {
    if (isEmpty())
        return "";

    string result = "{";
    auto temp = head;
    bool skipFirst = false;
    while (temp != nullptr) {
        if (skipFirst) {
            result += ", ";
        }
        skipFirst = true;
        result += temp->toString();
        temp = temp->next;
    }
    result += "}";
    return result;
}

PROVIDED_TEST("PointStack：打印栈元素") {
    PointStack pts;
    EXPECT_EQUAL(pts.toString(), "");
    pts.push(3, 5);
    pts.push(2, 4);
    cout << pts.toString() << endl;
    EXPECT_EQUAL(pts.toString(), "{(2, 4), (3, 5)}");
}
