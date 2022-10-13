/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "testing/SimpleTest.h"

using namespace std;

/*
 * @brief   operatorsFrom
 * ----------------------
 * @detail  recursively process string and return only symbol
 * @params  <string> str
 * @return  string
 */

string operatorsFrom(string str) {
    // process the first char, `if` can be returned
    if (str.length()!=0){
        if (!ispunct(str[0])) {return operatorsFrom(str.substr(1));}
        // process the left string and save to the result, recursively;
        else {return str[0] + operatorsFrom(str.substr(1));}
}
    return "";
}

/*
 * @brief   operatorsAreMatched
 * ----------------------------
 * @detail  check if operators are matched
 *          balance only when:
 *          1. string is blank
 *          2. string includes "()", "[]", "{}" etc.
 * @params  <string> ops
 * @return  <bool>
 */

#define v1
#ifdef v1
bool operatorsAreMatched(string ops) {
    if (ops.length() != 0){
        if (ops.find("()") != string::npos){
            ops.erase(ops.find("()"), 2);
            return operatorsAreMatched(ops);
        }

        if (ops.find("[]") != string::npos){
            ops.erase(ops.find("[]"), 2);
            return operatorsAreMatched(ops);
        }

        if (ops.find("{}") != string::npos){
            ops.erase(ops.find("{}"), 2);
            return operatorsAreMatched(ops);
        }
    }
    else {
        return true;
    }
    return false;
}
#endif

#ifdef v2
bool operatorsAreMatched(string ops) {
    if (!ops.empty()){
    if (ops[0] + 1 == ops[1]){
        ops.erase(0,2);
        return operatorsAreMatched(ops);
    }
    else {
        ops.replace(0, ops.length()-1);
        return operatorsAreMatched(ops.substr(1));
    }

    return true;
}
#endif


/*
 * The isBalanced function assumes correct implementation of
 * the above two functions operatorsFrom and operatorsMatch.
 * It uses operatorsFrom to extract the operator characters
 * from the input string and then confirms that those
 * operators are balanced by using operatorsMatch.
 * You should not modify the provided code in the isBalanced
 * function.  If the previous two functions have been implemented
 * correctly, the provided isBalanced will correctly report whether
 * the input string has balanced bracketing operators.
 */
bool isBalanced(string str) {
    string ops = operatorsFrom(str);
    return operatorsAreMatched(ops);
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
}

PROVIDED_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{}"));
    EXPECT(operatorsAreMatched("(())"));
    EXPECT(operatorsAreMatched("()[]"));
    EXPECT(!operatorsAreMatched("("));
}

PROVIDED_TEST("isBalanced on example from writeup") {
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on non-balanced examples from writeup") {
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}

/* * * * * * Student Cases * * * * * */

STUDENT_TEST("mytest1")
{
    EXPECT_EQUAL(operatorsFrom("ccaqwre()JLKJ{KJq123}"), "(){}");
    EXPECT_EQUAL(operatorsFrom(""), "");
    EXPECT_EQUAL(operatorsFrom("()"), "()");
}

