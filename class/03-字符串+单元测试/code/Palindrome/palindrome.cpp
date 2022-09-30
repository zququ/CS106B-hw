/**
 * File: palindrome.cpp
 * ---------------------
 */

#include "palindrome.h"
#include "strlib.h"
#include "testing/SimpleTest.h" // for testing

bool isPalindrome(std::string word) {
    // "" or "a"
    if (word.length() == 0 || word.length() == 1) {
        return true;
    }

    // pre: "level"
    //    char start = word[0]; // 'l'
    //    char end = word.at(word.length() - 1); // 'l'

    if (toLowerCase(word[0]) == toLowerCase(word.at(word.length() - 1))) {
        //        std::string rest = word.substr(1, word.length() - 2); // "eve"

        //        bool result = isPalindrome(rest);

        //        if (result) {
        //            return true;
        //        }

        return isPalindrome(word.substr(1, word.length() - 2));
    }

    return false;
}

// ********************* Test Case ****************

void isPalindromeTest(const std::string &word) {
    for (int i = 0; i < 1000000; i++) {
        isPalindrome(word);
    }
}

STUDENT_TEST("Normal Case") {
    EXPECT_EQUAL(isPalindrome("madam"), true);
    EXPECT_EQUAL(isPalindrome("level"), true);
    EXPECT_EQUAL(isPalindrome("level"), isPalindrome("madam"));

    EXPECT(isPalindrome("madam"));
    EXPECT(isPalindrome("level"));
}

STUDENT_TEST("相反测试") {
    EXPECT(!isPalindrome("good"));
    EXPECT(!isPalindrome("nice"));
}

STUDENT_TEST("Egde Case") {
    EXPECT(isPalindrome(""));
    EXPECT(isPalindrome("a"));
    EXPECT(isPalindrome("Level"));
}

STUDENT_TEST("Stress Case") {
    std::string word = "a";
    for (int i = 0; i < 16; i += 3) {
        TIME_OPERATION(word.length(), isPalindromeTest(word));
        word.append(word);
    }
}
