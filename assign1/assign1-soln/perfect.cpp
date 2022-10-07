/*
 * 测试几种不同的完全数寻找算法。
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

/*
 * 计算数子 n 的因子，并求出不包括自身的因子之和。
 *
 * 举例：
 * 1  -> 1               -> 0
 * 2  -> 1, 2            -> 1
 * 6  -> 1, 2, 3, 6      -> 6
 * 25 -> 1, 5, 25        -> 6
 *
 * 优化：根据因子的对称性，减少多余的搜索
 */
long smarterSum(long n) {
    // edge case
    if (n == 1)
        return 0;

    long total = 1; // 0 -> 1
    for (long divisor = 2; divisor < (sqrt(n) + 0.5); divisor++) { // 1 -> 2
        if (n % divisor == 0) {
            total += divisor;
            if(divisor != n / divisor)
                total += n / divisor;
        }
    }

    return total;
}

STUDENT_TEST("比较 divisorSum 和 smarterSum") {
    for (int i = 1; i < 1000; i++) {
        EXPECT_EQUAL(divisorSum(i), smarterSum(i));
    }
}

STUDENT_TEST("测试 smarterSum 平方根问题") {
    for (int i = 1; i < 1000; i++) {
        EXPECT_EQUAL(divisorSum(i*i), smarterSum(i*i));
    }
}

/* 相同逻辑 */
bool isPerfectSmarter(long n) {
    return (n != 0) && (n == smarterSum(n));
}

STUDENT_TEST("测试 isPerfectSmarter") {
    EXPECT(isPerfectSmarter(6));
    EXPECT(isPerfectSmarter(28));
    EXPECT(!isPerfectSmarter(12));
    EXPECT(!isPerfectSmarter(98765));
    EXPECT(!isPerfectSmarter(0));
    EXPECT(!isPerfectSmarter(1));
    EXPECT(isPerfectSmarter(33550336));
}

/* 相同逻辑 */
void findPerfectsSmarter(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

STUDENT_TEST("测试 findPerfectsSmarter") {
    TIME_OPERATION(10000, findPerfectsSmarter(10000));
    TIME_OPERATION(20000, findPerfectsSmarter(20000));
    TIME_OPERATION(40000, findPerfectsSmarter(40000));
}

/* 判断质数 */
bool isPrime(int n) {
    return smarterSum(n) == 1;
}

/* 采用欧几里得算法 */
long findNthPerfectEuclid(long n) {
    for (long k = 1; k < LONG_MAX; k++) {
        long m = pow(2, k) - 1;
        if (isPrime(m)) {
            if (--n == 0)
                return pow(2, k - 1) * m;
        }
    }

    return 0;
}

STUDENT_TEST("测试欧几里得算法") {
    EXPECT_EQUAL(findNthPerfectEuclid(1), (6));
    EXPECT_EQUAL(findNthPerfectEuclid(2), (28));
    EXPECT_EQUAL(findNthPerfectEuclid(3), (496));
    EXPECT_EQUAL(findNthPerfectEuclid(4), (8128));
    EXPECT_EQUAL(findNthPerfectEuclid(5), (33550336));
    //EXPECT(isPerfectSmarter(findNthPerfectEuclid(6)));
    //EXPECT(isPerfectSmarter(findNthPerfectEuclid(8)));
}

/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {

    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(10000, findPerfects(10000));
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
}

// TODO: add your student test cases here


