#include "vector.h"
#include <iostream>
using namespace std;

int main() {
    string s;
    cout << s << endl; // Output: ???

    char x = s[-1];
    cout << x << endl; // Output: ???

    // Vector
    Vector<int> v = {1, 3, 7};

    v += 9;
    v.add(5);

    cout << v[0] << endl;
    cout << v.get(v.size() - 1) << endl;

    //v[-1] = 2;
    //v.get(-1);
    v.set(2, 6);
    //v.set(8, 4);

    Vector<int> first = v.subList(0, 2);
    Vector<int> last = v.subList(2);

    v.remove(0);
    v.clear();

    //    Vector<int> v1 = {1, 2};
    //    for (int i = 0; i < v1.size(); i++) {
    //        v1.add(randomInteger(0, 100));
    //    }

    // better for-loop
    Vector<string> v2 = { "A", "B", "C" };

    for (int i = 0; i < v2.size(); i++) {
        cout << v2[i] << endl;
    }

    for (string elem: v2) {
       // for all the elems in the Vector v2.
        cout << elem << endl;
    }

    return 0;
}
