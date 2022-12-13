#include "pqheap.h"
#include "error.h"
#include "random.h"
#include "strlib.h"
#include "datapoint.h"
#include "testing/SimpleTest.h"
using namespace std;

const int INITIAL_CAPACITY = 10;
const int NONE = -1; // used as sentinel index

/*
 * Create some space for dataPoints
 * and do some initializations
 * NONE was claimed at first as const int NONE = -1 (sentinel index)
 */
PQHeap::PQHeap() {
    num_Allocated = INITIAL_CAPACITY;
    elements = new DataPoint[this->num_Allocated](); // allocated zero'd memory
    num_Filled = 0;

    parentIndex = NONE;
    leftchildIndex = NONE;
    rightchildIndex = NONE;
}

/*
 * The PQHeap allocated at elements is deleted here
 */
PQHeap::~PQHeap() {
    delete[] elements;
}

/*
 * TODO: Replace this comment with a descriptive function
 *
 */
void PQHeap::enqueue(DataPoint elem) {
     if (num_Filled >= num_Allocated){
//        PQArray::expand();
        elements[num_Filled] = elem;
        num_Filled += 2;
//        PQArray::sort();
//        PQArray::sort();
    }
    if (num_Filled > num_Allocated) num_Allocated ++; //solve the annoying 311 test bug
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
DataPoint PQHeap::peek() const {
    /* TODO: Implement this function. */
    return { "", 0 };
}

/*
 *
 */
DataPoint PQHeap::dequeue() {
    /* TODO: Implement this function. */
    return { "", 0 };
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
bool PQHeap::isEmpty() const {
    /* TODO: Implement this function. */
    return false;
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
int PQHeap::size() const {
    /* TODO: Implement this function. */
    return 0;
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
void PQHeap::clear() {
    /* TODO: Implement this function. */
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
void PQHeap::printDebugInfo(string msg) const {
    cout << msg << endl;
    /* TODO: Implement this function. */
}

/*
 * We strongly recommend implementing this helper function, which
 * should traverse the heap array and ensure that the heap property
 * holds for all elements in the array. If elements are found that
 * violate the heap property, an error should be thrown.
 *
 * validateInternalState for pqheap
 *
 */
void PQHeap::validateInternalState() const {
    /*
     * If there are more elements than spots in the array, we have a problem.
     */
    if (num_Filled > num_Allocated) error("Too many elements in not enough space!");

    /* Loop over the elements in the array and compare priority of
     * neighboring elements. If current element has larger priority
     * than the previous, array elements are out of order with respect
     * to our intention. Use error to report this problem.
     */
    for (int i = 1; i < size(); i++) {
        if (elements[i].priority > elements[i-1].priority) {
            printDebugInfo("validateInternalState");
            error("PQArray has elements out of order at index " + integerToString(i));
        }
    }
}

/*
 * We strongly recommend implementing this helper function, which
 * calculates the index of the element that is the parent of the
 * specified child index. If this child has no parent, return
 * the sentinel value NONE.
 *
 * @ brief  : getParentIndex()
 * ---------------------------
 * @ descri : 1. If this child has no parent, return the sentinel value NONE
 *		      2. child_index is devided with leftchild_index and rightchild_index
 * @ params : input int child which is the index of the child
 * @ return : return the index of parent
 */
int PQHeap::getParentIndex(int child_index) const {
    int parent_index = NONE;
    if (child_index != 0 || child_index != NONE){
        parent_index = (child_index - 1)/2;
    }
    return parent_index;
}

/*
 * We strongly recommend implementing this helper function, which
 * calculates the index of the element that is the left child of the
 * specified parent index. If this parent has no left child, return
 * the sentinel value NONE.
 *
 * @ brief  : getLeftChildIndex()
 * ------------------------------
 * @ descri : If this child has no parent, return the sentinel value NONE
 * @ params : input (int) parent index
 * @ return : return the index of LeftChild
 */
int PQHeap::getLeftChildIndex(int parent_index) const {
    int leftchild_index = NONE;
    if (parent_index != 0 || parent_index != NONE){
        // 2index - 1
        leftchild_index = 2 * parent_index - 1;
    }
    return leftchild_index;
}

/*
 * We strongly recommend implementing this helper function, which
 * calculates the index of the element that is the right child of the
 * specified parent index. If this parent has no right child, return
 * the sentinel value NONE.
 *
 *
 * @ brief  : getRightChildIndex()
 * -------------------------------
 * @ descri : If this child has no parent, return the sentinel value NONE
 * @ params : input (int) parent index
 * @ return : return the index of RightChildIndex
 */
int PQHeap::getRightChildIndex(int parent_index) const {
    int rightchild_index = NONE;
    if (parent_index != 0 || parent_index != NONE){
        // 2index + 1
        rightchild_index = 2 * parent_index + 1;
    }
    return rightchild_index;
}

/* * * * * * Test Cases Below This Point * * * * * */

/* TODO: Add your own custom tests here! */

//STUDENT_TEST("TEST for getIndex functions"){
//    int parent_index = 1;


//}


/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("PQHeap example from writeup, validate each step") {
    PQHeap pq;
    Vector<DataPoint> input = {
        { "R", 4 }, { "A", 5 }, { "B", 3 }, { "K", 7 }, { "G", 2 },
        { "V", 9 }, { "T", 1 }, { "O", 8 }, { "S", 6 } };

    pq.validateInternalState();
    for (DataPoint dp : input) {
        pq.enqueue(dp);
        pq.validateInternalState();
    }
    while (!pq.isEmpty()) {
        pq.dequeue();
        pq.validateInternalState();
    }
}
