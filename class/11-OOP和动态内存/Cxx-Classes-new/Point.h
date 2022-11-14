#ifndef POINT_H
#define POINT_H

#include <string>

class Point {
public:
    Point();
    Point(int x, int y);

    int getX();
    int getY();

    std::string toString();

private:
    int x;
    int y;

    // 自由函数无法访问私有成员变量，利用 friend 加好友，仅朋友圈可见
    friend bool operator!=(Point p1, Point p2);
};

// ***************** 自由函数 ******************
std::ostream &operator<<(std::ostream &os, Point pt);
bool operator==(Point p1, Point p2);

#endif // POINT_H
