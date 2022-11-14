#include "Point.h"
#include "strlib.h"
#include "testing/SimpleTest.h"
using std::cout;
using std::endl;

Point::Point(){
    x = 0;
    y = 0;
}

Point::Point(int x, int y){
    this->x = x;
    this->y = y;
}

int Point::getX(){
    return x;
}

int Point::getY(){
    return y;
}

std::string Point::toString() const{
    return '(' + integerToString(x) + ',' + integerToString(y) + ')';
}

bool operator != (Point p1, Point p2){
    return p1.getX() != p2.getX() || p1.getX() != p2.getX();
}

bool operator == (Point p1, Point p2){
    return p1.getX() == p2.getX() && p1.getY() == p2.getY();
}

// ***************** 自由函数 ******************
std::ostream &operator<<(std::ostream &os, Point point) {
    return os << point.toString();
}

// ***************** 测试 ******************

PROVIDED_TEST("测试 Point 类") {
    Point p1{3, 5};
    Point p2{5, 3};
    cout << p1 << endl;
    cout << p2 << endl;
    Point p3 = p1;
    EXPECT_EQUAL(p1, p3);
    EXPECT(p1 != p2);
    EXPECT(!(p1 == p2));
}
