/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include "queue.h"
#include "testing/SimpleTest.h"
using namespace std;

/* @brief       binaryMerge
 * @description 1. queue one and two has been ranked, returned value
 *                 should also be ranked with all elements in one and
 *                 two.
 *              2. queue one and two are transfered with value. So what
 *                 binaryMerge function get is a copy. And you can operate
 *                 this two values as you wish. There is no any requirement
 *                 about the end state of these queue copies.
 *              3. length of two queues are not required to be the seem.
 *                 One could be long and the other could be empty. Make sure
 *                 program can resolve all possibilities.
 *				4. replications are not need to be resolved, merge {1,2,2}
 *				   and {1, 3} will give {1,1,2,2,3}
 *              5. hint: you can split the mission to two sub-missions, make
 *				   sure the next elements to be solved and make it.
 *				6. important: you should use iteration but not recursive
 *				   to fullfil the binaryMerge. Because it is too expensive
 *			       to create a stack frame for each merged element.
 * @params		  Queue a and Queue b
 * @return      Merged Queue result
 */
Queue<int> binaryMerge(Queue<int> a, Queue<int> b) {
    const int size_a = a.size();
    const int size_b = b.size();
    Vector<int> vec_a={};
    Vector<int> vec_b={};
    Queue<int> result;

    if (!a.isEmpty()){
        for (int i = 0; i < size_a -1 ; i++){
            int cur_int  = a.dequeue();
            int next_int = a.peek();
            if (cur_int > next_int){
                error("the first input is not well sorted");
            } else {
                vec_a += cur_int;
            }
        }
            vec_a += a.dequeue(); // add the last elems after for recycling
                                  // aim to resolve the dequeue empty vector problem.
        } else {vec_a = {};}

    if(!b.isEmpty()){
        for (int i = 0; i < size_b - 1 ; i++){
            int cur_int2  = b.dequeue();
            int next_int2 = b.peek();
            if (cur_int2 > next_int2){
                error("the second input is not well sorted");
            } else {
                vec_b += cur_int2;
            }
        }
        vec_b += b.dequeue();
    } else {vec_b ={};}

    // put elems from vec_a to vec_b
    for (const int elems1 : vec_a){
        vec_b += elems1;
    }

    vec_b.sort();

    // from vector to queue
    for (const int &elems2 : vec_b){
        result.enqueue(elems2);
    }
    return result;
}

/*
 * This function assumes correct functionality of the previously
 * defined binaryMerge function and makes use of this function to
 * iteratively merge a collection of sequences, starting off with
 * an empty sequence and progressively merging in one sequence at
 * a time. This function is provided for you fully implemented –
 * it does not need to modified at all.
 */
Queue<int> naiveMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;

    for (Queue<int>& q : all) {
        result = binaryMerge(q, result);
    }
    return result;
}

/*
 * @brief       recMultiMerge
 * @description 1. cut k sequences into half
 *              2. call recMultiMerge resolve the first half. And reolve the second half
 *                 in the seem way.
 *              3. call binaryMerge to merge this two parts and return.
 * @params      Vector<Queue<int>> &all
 * @return      merged result
 */
Queue<int> recMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;
    Queue<int> l_result;
    Queue<int> r_result;
    int k = all.size();
    auto first_half = all.subList(0, k/2);
    auto second_half = all.subList(k/2);
    int l_k = first_half.size();
    int r_k = second_half.size();

    if (!first_half.isEmpty()){
        if (l_k <= 1) {
            l_result.enqueue(first_half[0].dequeue());
        }
        else {
            recMultiMerge(first_half);
        }
}
    if (!second_half.isEmpty()){
        if (r_k <=1) {
            r_result.enqueue(second_half[0].dequeue());
        }
        else {
            recMultiMerge(second_half);
        }
    }




//    int l_k = first_half.size();
//    int r_k = second_half.size();

//    if (l_k > 0){
//        if (l_k == 1) {
//            l_result = binaryMerge(first_half[0], {});
//        } else {
//            recMultiMerge(first_half);
//        }
//    }

//    if (r_k > 0){
//        if (r_k == 1) {
//            r_result = binaryMerge(second_half[0], {});
//        } else {
//            recMultiMerge(second_half);
//        }
//    }
//    result = binaryMerge(l_result, r_result);
    return result = binaryMerge(l_result, r_result);
}


/* * * * * * Test Cases * * * * * */

Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);

PROVIDED_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

PROVIDED_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

PROVIDED_TEST("recMultiMerge, compare to naiveMultiMerge") {
    int n = 20;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
}

PROVIDED_TEST("Time binaryMerge operation") {
    int n = 1000000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
}

PROVIDED_TEST("Time naiveMultiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), naiveMultiMerge(all));
}
PROVIDED_TEST("Time recMultiMerge operation") {
    int n = 90000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}


/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size) {
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}

/* Test helper to distribute elements of sorted sequence across k sequences,
   k is size of Vector */
void distribute(Queue<int> input, Vector<Queue<int>>& all) {
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size()-1)].enqueue(input.dequeue());
    }
}

STUDENT_TEST("not sorted sequence test if error"){
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 9, 2};
    EXPECT_ERROR(binaryMerge(a, b));
}
