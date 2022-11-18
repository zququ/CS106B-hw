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

void TestConstructorComplexity(const string& str) {
    LinkedString pts(str);
}
PROVIDED_TEST("LinkedString: Contructor Complexity") {
    string str = "Hello";
    for (int i = 0; i < 10; i++) {
        str += str;
    }
    for (int i = 0; i < 5; i++) {
        TIME_OPERATION(str.length(), TestConstructorComplexity(str));
        str += str;
    }
}

PROVIDED_TEST("LinkedString: strToLink/linkToStr") {
    LinkedString pts("Hello");
    string str = pts.toString();
    EXPECT_EQUAL(str, "Hello");
}

PROVIDED_TEST("LinkedString: sublink match") {
    string dna = "ACTGATGACT";
    LinkedString pts(dna);

    string target = "TGAC";

    string str = pts.toString();
    EXPECT_EQUAL(str, "Hello");
}
