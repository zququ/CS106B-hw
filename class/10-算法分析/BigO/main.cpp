#include "main.h"

#include <iostream>
using namespace std;

// 选择排序
void sort(Vector<int> &vec) {
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++) {
            if (vec[j] < vec[m])
                m = j;
        }
        int tmp = vec[i];
        vec[i] = vec[m];
        vec[m] = tmp;
    }
}

int maxOf(Vector<int> elems) {
    if (elems.size() == 1) {
        return elems[0];
    }

    int first = elems[0];
    Vector<int> rest = elems.subList(1);
    int maxOfRest = maxOf(rest);

    return first > maxOfRest ? first : maxOfRest;
}

int maxOfDevide(Vector<int> elems) {
    if (elems.size() == 1) {
        return elems[0];
    }

    int mid = elems.size() / 2;
    Vector<int> firstPart = elems.subList(0, mid);
    Vector<int> secondPart = elems.subList(mid);

    int maxOfFirst = maxOfDevide(firstPart);
    int maxOfSecond = maxOfDevide(secondPart);

    return maxOfFirst > maxOfSecond ? maxOfFirst : maxOfSecond;
}

int maxOfRefWrapper(const Vector<int> &elems, int start, int end) {
    if (end - start == 1) {
        return elems[start];
    }

    int mid = (end + start) / 2;
    int maxOfFirst = maxOfRefWrapper(elems, start, mid);
    int maxOfSecond = maxOfRefWrapper(elems, mid, end);

    return maxOfFirst > maxOfSecond ? maxOfFirst : maxOfSecond;
}

int maxOfRef(Vector<int> elems) {
    return maxOfRefWrapper(elems, 0, elems.size());
}
