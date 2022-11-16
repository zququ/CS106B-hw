#include "PointStack.h";
#include "testing/SimpleTest.h"

int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

    PointStack pts;
    if (pts.isEmpty()) {
        pts.push({3, 5});
        pts.push({3, 5});
        pts.push({3, 5});
    }
    cout << pts.toString() << endl;
//    return 0;

    ostringstream sout;
    sout << pts;
    cout << sout.str() << endl;
    return 0;
}
