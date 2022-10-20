/* File: Subsets.cpp
 *
 * A program to list off all subsets of a master set.
 */
#include "console.h"
#include "vector.h"
#include <iostream>
#include <string>
using namespace std;

#define rec1
#ifdef rec1
void listSubsetsRec(const Vector<int> &elems, Vector<int> &soFar, int index,
                    Vector<Vector<int>> &result) {
    if (index == elems.size()) {
        result.add(soFar);
    } else {
        for (const int item : elems) {
            soFar[index] = item;
            listSubsetsRec(elems, soFar, index + 1, result);
    }
}

}
void listSubSetsOf(const Vector<int> &elems) {
    Vector<int> soFar = {10,10,10};
    Vector<Vector<int>> result;
    listSubsetsRec(elems, soFar, 0, result);
    for (const Vector<int> &item : result) cout << item << endl;
}

int main() {
    Vector<int> elems = {1,3,5};
    listSubSetsOf(elems);
    return 0;
}
#endif
