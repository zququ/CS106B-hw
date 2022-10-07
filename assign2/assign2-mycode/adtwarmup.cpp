#include "testing/SimpleTest.h"
#include "set.h"
#include "queue.h"
#include "stack.h"
using namespace std;

/* This function correctly reverses the elements of a queue.
 */
void reverse(Queue<int>& q) {
    Stack<int> s;
    int val;

    while (!q.isEmpty()) {
        val = q.dequeue();
        s.push(val);
    }
    while (!s.isEmpty()) {
        val = s.pop();
        q.enqueue(val);
    }
}

/* This function is intended to modify a queue of characters to duplicate
 * any negative numbers.
 *
 * WARNING: the given code is buggy. See exercise writeup for more
 * information on how to test and diagnose.
 */
void duplicateNegatives(Queue<int>& q) {
    for (int i = 0; i < q.size(); i++) {
        int val = q.dequeue();
        q.enqueue(val);
        if (val < 0) {
            q.enqueue(val);
            i++; // double up on negative numbers
        }
    }
}

// This function is intended to return the sum of all values in
// the stack
// WARNING: the given code is buggy. See exercise writeup for more
// information on how to test and diagnose.
int sumStack(Stack<int> s) {
//    if (s.isEmpty()) {
//        return 0;
//    }
    s.push(0); //another way
    int total = s.pop();
    while (!s.isEmpty()) {
        total += s.pop();
    }
    return total;
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("reverse queue") {
    Queue<int> q = {1, 2, 3, 4, 5};
    Queue<int> expected = {5, 4, 3, 2, 1};

    reverse(q);
    EXPECT_EQUAL(q, expected);
}

PROVIDED_TEST("duplicateNegatives, input has no negatives") {
    Queue<int> q = {2, 10};
    Queue<int> expected = q;

    duplicateNegatives(q);
    EXPECT_EQUAL(q, expected);
}

PROVIDED_TEST("duplicateNegatives, input has one negative, one positive") {
    Queue<int> q = {-7, 9};
    Queue<int> expected = {-7, -7, 9};

    duplicateNegatives(q);
    EXPECT_EQUAL(q, expected);
}

PROVIDED_TEST("duplicateNegatives, input has negatives interspersed with positives") {
    Queue<int> q = {-3, 4, -5, 10};
    Queue<int> expected = {-3, -3, 4, -5, -5, 10};

    duplicateNegatives(q);
    EXPECT_EQUAL(q, expected);
}

PROVIDED_TEST("sumStack, 3 elements") {
    Stack<int> s = {1, 8, -5};

    EXPECT_EQUAL(sumStack(s), 4);
}

PROVIDED_TEST("sumStack, empty stack") {
    Stack<int> empty;

    EXPECT_EQUAL(sumStack(empty), 0);
}
STUDENT_TEST("all negatives student test") {
    Queue<int> q = {-3, -4, -5, -10};
    Queue<int> expected = {-3, -3, -4, -4, -5, -5, -10, -10};

    duplicateNegatives(q);
    EXPECT_EQUAL(q, expected);
}
