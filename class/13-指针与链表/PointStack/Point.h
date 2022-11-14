#ifndef POINT_H
#define POINT_H
#include "testing/MemoryDiagnostics.h"
#include <string>

class Point {
public:
    Point *next{nullptr}; // 用于链接另一个 Point 对象
    TRACK_ALLOCATIONS_OF(Point);

    Point();
    Point(int x, int y);

    int getX();
    int getY();

    std::string toString() const;

private:
    int x;
    int y;

    friend bool operator!=(Point p1, Point p2);
    friend bool operator==(Point p1, Point p2);
};

// ***************** 自由函数 ******************
std::ostream &operator<<(std::ostream &os, Point pt);

#endif // POINT_H
