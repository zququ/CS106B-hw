#include "main.h"

#include <fstream>
#include <iomanip>
#include <iostream>

#include "utility.h"

using namespace std;

void selectionSort(Vector<int>& elems) {
    for (int index = 0; index < elems.size(); index++) {
        int smallestIndex = indexOfSmallest(elems, index);
        swap(elems, index, smallestIndex);
    }
}

int indexOfSmallest(const Vector<int>& elems, int startPoint) {
    int smallestIndex = startPoint;
    for (int i = startPoint + 1; i < elems.size(); i++) {
        if (elems[i] < elems[smallestIndex]) {
            smallestIndex = i;
        }
    }
    return smallestIndex;
}

void insertionSort(Vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (v[j] <= v[j + 1]) break;
            swap(v, j, j + 1);
        }
    }
}

void mergeSort(Vector<int>& vec) {
    if (vec.size() <= 1) return;

    Vector<int> left, right;
    split(vec, left, right);

    mergeSort(left);
    mergeSort(right);

    vec = {};
    merge(vec, left, right);
}

void split(Vector<int>& vec, Vector<int>& left, Vector<int>& right) {
    int n = vec.size();
    left = vec.subList(0, n / 2);
    right = vec.subList(n / 2);
}

void merge(Vector<int>& vec, Vector<int>& v1, Vector<int>& v2) {
    int n1 = v1.size();
    int n2 = v2.size();
    int idx1 = 0;
    int idx2 = 0;
    while (idx1 < n1 && idx2 < n2) {
        if (v1[idx1] < v2[idx2]) {
            vec.add(v1[idx1]);
            idx1++;
        } else {
            vec.add(v2[idx2]);
            idx2++;
        }
    }

    while (idx1 < n1) {
        vec.add(v1[idx1]);
        idx1++;
    }

    while (idx2 < n2) {
        vec.add(v2[idx2]);
        idx2++;
    }
}
