#include "Point.h"
#include "testing/SimpleTest.h"
#include <iostream>
using namespace std;

int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

    return 0;
}

PROVIDED_TEST("小试牛刀") {
    Point* list;
    list = nullptr;
    list = new Point;
    cout << (*list).getX() << endl;
    cout << (*list).getY() << endl;
    cout << list->toString() << endl;
    delete list;
}
