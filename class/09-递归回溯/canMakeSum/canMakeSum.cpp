/* File: Permutations.cpp
 *
 * A program to list off all subsets of a master set.
 */
#include <iostream>
#include <string>

#include "console.h"
#include "testing/SimpleTest.h"
#include "vector.h"
using namespace std;

#define btr

#ifdef btr
// 递归回溯：another bactracking
bool canMakeSumRec(Vector<int> &v, int index, int target) {
    if (target == 0) {
        return true;
    } else {
        for (int i = index; i < v.size(); i++) {
            if (canMakeSumRec(v, i + 1, target - v[i]))
                return true;
        }
    }

    return false;
}
#endif

#ifdef dfs
// 递归回溯：DFS
bool canMakeSumRec(Vector<int> &v, int index, int target) {
    if (index == v.size()) {
        if (target == 0)
            return true;
    } else {
        // include
        if (canMakeSumRec(v, index + 1, target - v[index]))
            return true;
        // exclude
        if (canMakeSumRec(v, index + 1, target))
            return true;
    }

    return false;
}
#endif

bool canMakeSum(Vector<int> &v, int target) {
    return canMakeSumRec(v, 0, target);
}

int main() {
    if (runSimpleTests(SELECTED_TESTS))
        return 0;

    return 0;
}

// ******************* Testing ********************

STUDENT_TEST("Test {1, 1, 2, 3, 5} and 9") {
    Vector<int> elems = {1, 1, 2, 3, 5};
    EXPECT(canMakeSum(elems, 9));
}

STUDENT_TEST("Test {1, 4, 5, 6} and 8") {
    Vector<int> elems = {1, 4, 5, 6};
    EXPECT(!canMakeSum(elems, 8));
}

STUDENT_TEST("Test {} and 4") {
    Vector<int> elems = {};
    EXPECT(!canMakeSum(elems, 4));
}
