#ifndef POINT_H
#define POINT_H

#include <string>

class Point{
public:
    Point();
    Point(int x, int y);

    int getX();
    int getY();

    std::string toString() const;

private:
    int x;
    int y;

    friend bool operator !=(Point p1, Point p2);
    friend bool operator ==(Point p1, Point p2);
};
// ***************** 自由函数 ******************
std::ostream &operator<<(std::ostream &os, Point pt);

#endif // POINT_H
