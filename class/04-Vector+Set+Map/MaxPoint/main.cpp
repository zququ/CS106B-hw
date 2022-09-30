/**
 * Find the max point in the given Vector.
 */
#include "random.h"
#include "testing/SimpleTest.h"
#include "vector.h"

int maxOf(Vector<int> elems) {
    // edge case
    if (elems.size() == 1) {
        return elems[0];
    }

    // pick the first point
    int first = elems[0];

    // get the max point in the rest (someone do it for you)
    Vector<int> rest = elems.subList(1);
    int maxOfRest = maxOf(rest);

    // compare your point with the max point in the rest
    return first > maxOfRest ? first : maxOfRest;
}

int maxOfDevide(Vector<int> elems) {
    // edge case
    if (elems.size() == 1) {
        return elems[0];
    }

    int mid = elems.size() / 2;
    Vector<int> firstPart = elems.subList(0, mid);
    Vector<int> secondPart = elems.subList(mid);

    // get the max point in the first part
    int maxOfFirst = maxOfDevide(firstPart);
    // get the max point in the second part
    int maxOfSecond = maxOfDevide(secondPart);

    // compare
    return maxOfFirst > maxOfSecond ? maxOfFirst : maxOfSecond;
}

int maxOfRef(Vector<int> &elems, int start, int end) {
    // edge case
    if (end - start == 1) {
        return elems[start];
    }

    int mid = (end + start) / 2;
    // first part
    int maxOfFirst = maxOfRef(elems, start, mid);
    // second part
    int maxOfSecond = maxOfRef(elems, mid, end);

    // compare
    return maxOfFirst > maxOfSecond ? maxOfFirst : maxOfSecond;
}

int main() {
    if (runSimpleTests(SELECTED_TESTS))
        return 0;

    return 0;
}

// *********************** Testing Case ****************************

void maxOfTest(Vector<int> &v) {
    for (int i = 0; i < 10; i++) {
        maxOf(v);
    }
}

void maxOfDevideTest(Vector<int> &v) {
    for (int i = 0; i < 10; i++) {
        maxOfDevide(v);
    }
}

void maxOfRefTest(Vector<int> &v) {
    for (int i = 0; i < 10; i++) {
        maxOfRef(v, 0, v.size());
    }
}

PROVIDED_TEST("Egde Testing for maxOf") {
    Vector<int> v = {137};
    EXPECT_EQUAL(maxOf(v), 137);
}

PROVIDED_TEST("Normal Testing for maxOf") {
    Vector<int> v = {137, 106, 107, 166, 103};
    EXPECT_EQUAL(maxOf(v), 166);
}

PROVIDED_TEST("Stress Testing for maxOf") {
    Vector<int> v;
    for (int n = 0; n < 5; n++) {
        for (int i = v.size() ? v.size() : 500; i > 0; i--) {
            v.add(randomInteger(-1000, 1000));
        }
        TIME_OPERATION(v.size(), maxOfTest(v));
    }
}

PROVIDED_TEST("Egde Testing for maxOfDevide") {
    Vector<int> v = {137};
    EXPECT_EQUAL(maxOfDevide(v), 137);
}

PROVIDED_TEST("Normal Testing for maxOfDevide") {
    Vector<int> v = {137, 106, 107, 166, 103};
    EXPECT_EQUAL(maxOfDevide(v), 166);
}

PROVIDED_TEST("Stress Testing for maxOfDevide") {
    Vector<int> v;
    for (int n = 0; n < 5; n++) {
        for (int i = v.size() ? v.size() : 500; i > 0; i--) {
            v.add(randomInteger(-1000, 1000));
        }
        TIME_OPERATION(v.size(), maxOfDevideTest(v));
    }
}

PROVIDED_TEST("Egde Testing for maxOf") {
    Vector<int> v = {137};
    EXPECT_EQUAL(maxOfRef(v, 0, v.size()), 137);
}

PROVIDED_TEST("Normal Testing for maxOf") {
    Vector<int> v = {137, 106, 107, 166, 103};
    EXPECT_EQUAL(maxOfRef(v, 0, v.size()), 166);
}

PROVIDED_TEST("Stress Testing: Reference") {
    Vector<int> v;
    for (int n = 0; n < 5; n++) {
        for (int i = v.size() ? v.size() : 500; i > 0; i--) {
            v.add(randomInteger(-1000, 1000));
        }
        TIME_OPERATION(v.size(), maxOfRefTest(v));
    }
}
