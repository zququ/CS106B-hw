/**
 * Find the max point in the given Vector.
 */
#include "random.h"
#include "testing/SimpleTest.h"
#include "vector.h"

int maxOf(Vector<int> elems) {
    // don't accept any parameters

    // edge case
    if (elems.size() == 1){
        return elems[0];
    }
    // pick the first point
    int first=elems[0];

    // get the max point in the rest (someone do it for you)
    Vector<int> rest=elems.subList(1);
    int maxofrest = maxOf(rest);

    // compare your point with the max point in the rest
    return first > maxofrest ? first : maxofrest;
}

int maxOfDevide(Vector<int> elems) {
    (void)elems;
    // edge case
    if (elems.size()== 1){
        return elems[0];
    }
    // divide the task into two parts
    int mid = elems.size()/2;
    Vector<int> leftpart = elems.subList(0,mid);
    Vector<int> rightpart = elems.subList(mid);
    // get the max point in the first part
    int maxleftpart = maxOfDevide(leftpart);
    // get the max point in the second part
    int maxrightpart = maxOfDevide(rightpart);
    // compare the two max points
    return maxleftpart > maxrightpart ? maxleftpart: maxrightpart;
}

int maxOfRef(Vector<int> &elems, int start, int end) {
    (void)elems;
    (void)start;
    (void)end;
    // edge case
    if (end - start == 1){
        return elems[start];
    }
    // divide the task into two parts
    int mid = (end + start)/2;
    // get the max point in the first part
    int maxleftpart = maxOfRef(elems, start, mid);
    // get the max point in the second part
    int maxrightpart = maxOfRef(elems, mid, end);
    // compare the two max points
    return maxleftpart > maxrightpart ? maxleftpart : maxrightpart;
}

int main() {
    if (runSimpleTests(SELECTED_TESTS))
        return 0;

    return 0;
}

// *********************** Testing Case ****************************

//void maxOfRefTest(Vector<int> &v) {
//    for (int i = 0; i < 10; i++){
//        maxOfRef(v, 0, v.size());
//    }
//}

STUDENT_TEST("Edge testing: single elem vector test") {
    Vector<int> v = {137};
    EXPECT_EQUAL(maxOfRef(v, 0, v.size()), 137);
}

STUDENT_TEST("Normal testing: normal elems vector test"){
    Vector<int> v = {137, 106, 107, 166, 103};
    EXPECT_EQUAL(maxOfRef(v, 0, v.size()), 166);
}
STUDENT_TEST("Stress Testing: Reference") {
    Vector<int> v;
    for (int n = 0; n < 5; n++) {
        for (int i = v.size() ? v.size() : 5; i > 0; i--) {
            v.add(randomInteger(-1000, 1000));
        }
//        TIME_OPERATION(v.size(), maxOfRefTest(v));
        TIME_OPERATION(v.size(), maxOfRef(v, 0, v.size()));
    }
}
