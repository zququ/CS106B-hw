/* File: Subsets.cpp
 *
 * A program to list off all subsets of a master set.
 */
#include <iostream>
#include <string>

#include "console.h"
#include "vector.h"
using namespace std;

#define version_3

#ifdef version_3
// 递归法求排列：Choose/Explore/Unchoose Pattern
void listPermutationsRec(const Vector<int> &elems, Vector<int> &soFar, int index,
                         Vector<Vector<int>> &result) {
    // 1. Base Case：索引达到结尾
    if (index == elems.size()) {
        result.add(soFar);
    } else {
        for (const int item : elems) {
            // 2.1 Choose
            soFar[index] = item;
            // 2.2 Explore
            listPermutationsRec(elems, soFar, index + 1, result);
            // 2.3 Unchoose
        }
    }
}

void listPermutationsOf(const Vector<int> &elems) {
    Vector<int> soFar = {0, 0, 0};
    Vector<Vector<int>> result;
    listPermutationsRec(elems, soFar, 0, result);
    for (const Vector<int> &item : result) cout << item << endl;
}

int main() {
    Vector<int> elems = {1, 3, 5};
    listPermutationsOf(elems);
    return 0;
}
#endif

#ifdef version_2
// 递归法求排列：子集的引申
void listSubsetsRec(const Vector<int> &elems, Vector<int> &soFar, int index,
                    Vector<Vector<int>> &result) {
    if (index == elems.size()) {
        result.add(soFar);
    } else {
        soFar[index] = elems[index];
        listSubsetsRec(elems, soFar, index + 1, result);
        soFar[index] = 0;
        listSubsetsRec(elems, soFar, index + 1, result);
    }
}

void listSubsetsOf(const Vector<int> &elems) {
    Vector<int> soFar = {0, 0, 0};
    Vector<Vector<int>> result;
    listSubsetsRec(elems, soFar, 0, result);
    for (const Vector<int> &item : result) cout << item << endl;
}

int main() {
    Vector<int> elems = {1, 1, 1};
    listSubsetsOf(elems);
    return 0;
}
#endif

#ifdef version_1
// 递归法求子集：引用参数
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
