/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include "testing/SimpleTest.h"
using namespace std;

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: change the upper limit of divisor to sqrt(n), attention
 * for `<=`
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */

long smarterSum(long n) {
    long total = 0;
    for (long divisor = 2; divisor <= sqrt(n); divisor++){
        if (n % divisor == 0){
            total += (divisor + n/divisor);
        }
    }
    return total+1;
}

/* SmarterVersion
 * --------------
 * This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfectSmarter(long n) {
    return (n != 0) && (n != 1) && (n == smarterSum(n));
}

/* SmarterVersion
 * --------------
 * This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfectsSmarter(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
long findNthPerfectEuclid(long n) {
    if (n == 0){
        return NULL;
    }
    if (n < 0){
        return NULL;
    }
    long count = 0;
    long MaxPerfect_m = 0;
    for (long k = 1; n > 0; k++){
        long m = pow(2, k) - 1;
        if (smarterSum(m) == 1 && m!=1){
            long Perfect_m = pow(2, k-1) * (pow(2, k) - 1);
            cout << "Found perfect number: " << Perfect_m << endl;
            n--;
            count ++;
            MaxPerfect_m = Perfect_m;
        }
    }
//    cout << endl << "Done searching up to " << count << endl;
    return MaxPerfect_m;
}

/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

//PROVIDED_TEST("Confirm divisorSum of small inputs") {
//    EXPECT_EQUAL(divisorSum(1), 0);
//    EXPECT_EQUAL(divisorSum(6), 6);
//    EXPECT_EQUAL(divisorSum(12), 16);
//}

//PROVIDED_TEST("Confirm 6 and 28 are perfect") {
//    EXPECT(isPerfect(6));
//    EXPECT(isPerfect(28));
//}

//PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
//    EXPECT(!isPerfect(12));
//    EXPECT(!isPerfect(98765));
//}

//PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
//    EXPECT(!isPerfect(0));
//    EXPECT(!isPerfect(1));
//}

//PROVIDED_TEST("Confirm 33550336 is perfect") {
//    EXPECT(isPerfect(33550336));
//}

//PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
//    TIME_OPERATION(15000, findPerfects(15000));
//    TIME_OPERATION(30000, findPerfects(30000));
//    TIME_OPERATION(60000, findPerfects(60000));
//    TIME_OPERATION(120000, findPerfects(120000));
//}

//// TODO: add your student test cases here

//// negative value test
//STUDENT_TEST("Confirm -6 and -28 are not perfect") {
//    EXPECT(!isPerfect(-6));
//    EXPECT(!isPerfect(-28));
//}
//// perfect number test
//STUDENT_TEST("Confirm 6 and 28 are perfect") {
//    EXPECT(isPerfectSmarter(6));
//    EXPECT(isPerfectSmarter(28));
//}

//// bigger perfect number test
//STUDENT_TEST("Confirm 33550336 is perfect") {
//    EXPECT(isPerfectSmarter(33550336));
//}

//// edged number test
//STUDENT_TEST("Confirm 25 is not perfect") {
//    EXPECT(!isPerfectSmarter(25));
//}

//speed test
//STUDENT_TEST("Time trials of findPerfects on doubling input sizes") {
//    TIME_OPERATION(500000, findPerfectsSmarter(500000));
//    TIME_OPERATION(1000000, findPerfectsSmarter(1000000));
//    TIME_OPERATION(2000000, findPerfectsSmarter(2000000));
//    TIME_OPERATION(4000000, findPerfectsSmarter(4000000));
//}


// student test for findNthPerfectEuclid()

//negative test
STUDENT_TEST("Confirm find 1 perfect number is ok."){
    EXPECT(isPerfect(findNthPerfectEuclid(1)));
}

// edged test

STUDENT_TEST("Confirm find 0 perfect number is will not make troubles."){
    EXPECT(!isPerfect(findNthPerfectEuclid(0)));
}

STUDENT_TEST("Confirm find 5 perfect number is ok." ){
    EXPECT(isPerfect(findNthPerfectEuclid(5)));
}

// large number calculation test
STUDENT_TEST("Confirm find 6 perfect number is ok." ){
    EXPECT(isPerfect(findNthPerfectEuclid(6)));
}

// speed test for findNthPerfectEuclid(5)
STUDENT_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(1, findNthPerfectEuclid(1));
    TIME_OPERATION(2, findNthPerfectEuclid(2));
    TIME_OPERATION(3, findNthPerfectEuclid(3));
    TIME_OPERATION(4, findNthPerfectEuclid(4));
    TIME_OPERATION(5, findNthPerfectEuclid(5));
}
