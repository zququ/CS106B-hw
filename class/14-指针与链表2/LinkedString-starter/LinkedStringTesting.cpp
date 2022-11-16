#include "LinkedString.h"
#include "testing/SimpleTest.h"
#include <string>
using std::string;

PROVIDED_TEST("LinkedString: Contructor/Destructor") {
    LinkedString pts;
    (void)pts;
    LinkedString pts2("Hello");
    (void)pts2;
}

PROVIDED_TEST("LinkedString: strToLink/linkToStr") {
    LinkedString pts("Hello");
    string str = pts.toString();
    EXPECT_EQUAL(str, "Hello");
}

void TestConstructorComplexity(const string& str) {
    LinkedString pts(str);
}
PROVIDED_TEST("LinkedString: Stress Testing") {
    string str = "Hello";
    for (int i = 0; i < 10; i++) {
        str += str;
    }
    for (int i = 0; i < 2; i++) {
        TIME_OPERATION(str.length(), TestConstructorComplexity(str));
        str += str;
    }
}
