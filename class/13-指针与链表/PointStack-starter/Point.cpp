#include "Point.h"
#include "strlib.h"
#include "testing/SimpleTest.h"
using std::cout;
using std::endl;

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

int Point::getX() {
    return x;
}

int Point::getY() {
    return y;
}

std::string Point::toString() const {
    return "(" + integerToString(x) + ", " + integerToString(y) + ")";
}

bool operator!=(Point p1, Point p2) {
    return p1.x != p2.x || p1.y != p2.y;
}

bool operator==(Point p1, Point p2) {
    return p1.getX() == p2.getX() && p1.getY() == p2.getY();
}

// ***************** 自由函数 ******************
std::ostream &operator<<(std::ostream &os, Point pt) {
    return os << pt.toString();
}
