/* File: Subsets.cpp
 *
 * A program to list off all subsets of a master set.
 */
#include "console.h"
#include "vector.h"
#include <iostream>
#include <string>
using namespace std;

#define version_e
#ifdef version_e
void listSubsetsOfRec(const Vector<int> &elems,
                      int index,
                      Vector<int> &soFar,
                      int total,
                      Vector<Vector<int>> &result) {
    // 1. Base Case
    if (index == elems.size()) {
        if (total > 6) {
            result.add(soFar);
        }
    } else {
        // 2. Reducing
        int item = elems[index];
        index += 1;

        // pre-condition: sofar = {}

        // 3.1 Include
        soFar.add(item);
        // pre-condition: sofar = {1}
        listSubsetsOfRec(elems, index, soFar, total + item, result);
        // post-condition: sofar = {1}

        // 3.2 Exclude
        // pre-condition: sofar = {1}
        soFar.remove(soFar.size() - 1);
        // post-condition: sofar = {}
        listSubsetsOfRec(elems, index, soFar, total, result);
    }
}

void listSubsetsOf(const Vector<int> &elems) {
    Vector<Vector<int>> result;
    Vector<int> sofar;
    listSubsetsOfRec(elems, 0, sofar, 0, result);
    for (const auto &subset : result) {
        cout << subset << endl;
    }
}

int main() {
    Vector<int> elems = {1, 3, 5, 7};
    listSubsetsOf(elems);
    return 0;
}
#endif

#ifdef version_d
void listSubsetsOfRec(const Vector<int> &elems,
                      int index,
                      Vector<int> &soFar,
                      Vector<Vector<int>> &result) {
    // 1. Base Case
    if (index == elems.size()) {
        result.add(soFar);
    } else {
        // 2. Reducing
        int item = elems[index];
        index += 1;

        // pre-condition: sofar = {}

        // 3.1 Include
        soFar.add(item);
        // pre-condition: sofar = {1}
        listSubsetsOfRec(elems, index, soFar, result);
        // post-condition: sofar = {1}

        // 3.2 Exclude
        // pre-condition: sofar = {1}
        soFar.remove(soFar.size() - 1);
        // post-condition: sofar = {}
        listSubsetsOfRec(elems, index, soFar, result);
    }
}

void listSubsetsOf(const Vector<int> &elems) {
    Vector<Vector<int>> result;
    Vector<int> sofar;
    listSubsetsOfRec(elems, 0, sofar, result);
    for (const auto &subset : result) {
        int total = 0;
        for (const int item : subset) {
            total += item;
        }
        if (total > 5) {
            cout << subset << endl;
        }
    }
}

int main() {
    Vector<int> elems = {1, 3, 5};
    listSubsetsOf(elems);
    return 0;
}
#endif

#ifdef version_c
Vector<Vector<int>> listSubsetsOfRec(const Vector<int> &elems, const Vector<int> &soFar) {
    Vector<Vector<int>> result;
    // 1. Base Case
    if (elems.isEmpty()) {
        result.add(soFar);
    } else {
        // 2. Reducing
        int item = elems[0];
        auto remains = elems.subList(1);
        // 3.1 Include
        result += listSubsetsOfRec(remains, soFar + item);
        // 3.2 Exclude
        result += listSubsetsOfRec(remains, soFar);
    }

    return result;
}

void listSubsetsOf(const Vector<int> &elems) {
    Vector<Vector<int>> result = listSubsetsOfRec(elems, {});
    for (const auto &subset : result) {
        cout << subset << endl;
    }
}

int main() {
    Vector<int> elems = {1, 3, 5};
    listSubsetsOf(elems);
    return 0;
}
#endif

#ifdef version_b
void listSubsetsOfRec(const Vector<int> &elems, const Vector<int> &soFar) {
    // 1. Base Case
    if (elems.isEmpty()) {
        cout << soFar << endl;
    } else {
        // 2. Reducing
        int item = elems[0];
        auto remains = elems.subList(1);
        // 3.1 Include
        listSubsetsOfRec(remains, soFar + item);
        // 3.2 Exclude
        listSubsetsOfRec(remains, soFar);
    }
}

void listSubsetsOf(const Vector<int> &elems) {
    listSubsetsOfRec(elems, {});
}

int main() {
    Vector<int> elems = {1, 2, 3};
    listSubsetsOf(elems);
    return 0;
}
#endif

#ifdef version_a
// 迭代法求子集
void listSubsetsOf(Vector<int> &elems) {
    Vector<Vector<int>> subsets = {{}};
    for (int i = 0; i < elems.size(); i++) {
        int size = subsets.size();
        for (int j = 0; j < size; j++)
            subsets.add(subsets[j] + elems[i]);
    }
    for (const auto &subset : subsets)
        cout << subset << endl;
}

int main() {
    Vector<int> elems = {1, 2, 3};
    listSubsetsOf(elems);
    return 0;
}
#endif
