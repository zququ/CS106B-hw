/* File: Permutations.cpp
 *
 * A program to list off all subsets of a master set.
 */
#include <iostream>
#include <string>

#include "console.h"
#include "vector.h"
using namespace std;

#define btr

#ifdef btr
// 递归回溯：another bactracking
void listSubsetsRec(const Vector<int> &elems, Vector<int> &soFar, int index, Vector<Vector<int>> &result) {
    result.add(soFar);
    for (int i = index; i < elems.size(); i++) {
        soFar.add(elems[i]);
        listSubsetsRec(elems, soFar, i + 1, result);
        soFar.remove(soFar.size() - 1);
    }
}

void listSubsetsOf(const Vector<int> &elems) {
    Vector<int> soFar;
    Vector<Vector<int>> result;
    listSubsetsRec(elems, soFar, 0, result);
    for (const Vector<int> &item : result)
        cout << item << endl;
}

int main() {
    Vector<int> elems = {1, 3, 5};
    listSubsetsOf(elems);
    return 0;
}
#endif

#ifdef dfs
// 递归回溯：DFS 版
void listSubsetsRec(const Vector<int> &elems, Vector<int> &soFar, int index,
                    Vector<Vector<int>> &result) {
    if (index == elems.size()) {
        result.add(soFar);
    } else {
        soFar.add(elems[index]);
        listSubsetsRec(elems, soFar, index + 1, result);
        soFar.remove(soFar.size() - 1);
        listSubsetsRec(elems, soFar, index + 1, result);
    }
}

void listSubsetsOf(const Vector<int> &elems) {
    Vector<int> soFar;
    Vector<Vector<int>> result;
    listSubsetsRec(elems, soFar, 0, result);
    for (const Vector<int> &item : result) cout << item << endl;
}

int main() {
    Vector<int> elems = {1, 3, 5};
    listSubsetsOf(elems);
    return 0;
}
#endif
