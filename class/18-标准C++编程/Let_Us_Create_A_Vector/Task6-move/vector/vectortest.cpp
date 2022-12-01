#include "testing/SimpleTest.h"
#include "vector.h"
using namespace cs101;
using std::cout;
using std::endl;

void passByRef(const vector<std::string>& vec) {
    std::cout << "passed by reference:" << std::endl;
    std::cout << vec << std::endl;
}

void passByVal(const vector<std::string> vec) {
    std::cout << "passed by value:" << std::endl;
    std::cout << vec << std::endl;
}

vector<std::string> returnByVal(
    vector<std::string> vec) {
    cout << "return by value:" << endl;
    return vec;
}

PROVIDED_TEST("Rule of Five") {
    cout << endl << "构造 2 个对象" << endl;
    vector<std::string> vec1(3, "A");
    vector<std::string> vec2(3, "B");
    cout << "vec1: " << vec1 << endl;
    cout << "vec2: " << vec2 << endl << endl;

    cout << "移动临时对象" << endl;
    vector<std::string> vec3;
    vec3 = returnByVal(vec1);
    cout << "vec3: " << vec3 << endl << endl;

    cout << "移动临时对象" << endl;
    vector<std::string> vec4;
    vec4 = vec1 + vec2;
    cout << "vec4: " << vec4 << endl << endl;
}

PROVIDED_TEST("Rule of Three") {
    cout << endl << "构造 3 个对象" << endl;
    vector<std::string> vec1(3, "A");
    vector<std::string> vec2(3, "B");
    vector<std::string> vec3(3, "C");
    cout << "vec1: " << vec1 << endl;
    cout << "vec2: " << vec2 << endl;
    cout << "vec3: " << vec3 << endl << endl;

    cout << "引用传递对象" << endl;
    passByRef(vec1);
    cout << "vec1: " << vec1 << endl << endl;

    cout << "传值传递对象" << endl;
    passByVal(vec2);
    cout << "vec2: " << vec2 << endl << endl;

    cout << "用现有对象构造对象" << endl;
    vector<std::string> vec4 = vec3;
    cout << "vec4: " << vec4 << endl << endl;

    cout << "把一个对象赋值给另一个对象" << endl;
    vector<std::string> vec5;
    vec5 = vec1;
    cout << "vec5: " << vec5 << endl << endl;
}

PROVIDED_TEST("Subscript [] Operator") {
    vector<int> intVec(3, 10);
    intVec[0] = 12;

    EXPECT_EQUAL(intVec[0], 12);
    EXPECT_EQUAL(intVec[1], intVec[2]);
}

PROVIDED_TEST("Insertion << Operator") {
    vector<int> intVec(3, 10);
    std::cout << intVec << std::endl;

    vector<std::string> strVec(3, "abc");
    std::cout << strVec << std::endl;
}

PROVIDED_TEST("Conversion Operators") {
    vector<int> intVec;
    //intVec = 10; // explicit

    if(intVec){
        std::cout << "Empty!" << std::endl;
    }
}

PROVIDED_TEST("const-correctness") {
    vector<int> intVec(3, 10);
    //if(intVec.at(1) = 1){
    if(intVec.at(1) == 1){
        std::cout << "intVec.at(1) == 1" << std::endl;
    }

    intVec.front() -= intVec.back();
    EXPECT_EQUAL(intVec.front(), 0);
}

PROVIDED_TEST("const-interface") {
    const vector<int> intVec(3, 10);
    intVec.size();
    intVec.at(1);

    // using const_iterator
    for (auto itr = intVec.begin(); itr < intVec.end(); ++itr) {
        std::cout << *itr << std::endl;
        EXPECT_EQUAL(*itr, 10);
    }
}

PROVIDED_TEST("template") {
    vector<double> doubleVec(3, 3.14);
    for (auto itr = doubleVec.begin(); itr < doubleVec.end(); ++itr) {
        std::cout << *itr << std::endl;
        EXPECT_EQUAL(*itr, 3.14);
    }

    vector<std::string> strVec(3, "abc");
    for (auto itr = strVec.begin(); itr < strVec.end(); ++itr) {
        std::cout << *itr << std::endl;
        EXPECT_EQUAL(*itr, "abc");
    }
}

PROVIDED_TEST("namespace") {
    using namespace std;
    // vector<int> intVec; // ambiguous
}

PROVIDED_TEST("iterator") {
    vector<int> intVec(3, 10);
    for (auto itr = intVec.begin(); itr < intVec.end(); ++itr) {
        std::cout << *itr << std::endl;
        EXPECT_EQUAL(*itr, 10);
    }
}

// ToDo1
PROVIDED_TEST("reserve") {
    vector<int> intVec;
    EXPECT_EQUAL(intVec.capacity(), 10);

    vector<int> intVec2(20);
    EXPECT_EQUAL(intVec2.capacity(), 20);

    intVec.reserve(30);
    EXPECT_EQUAL(intVec.capacity(), 30);
}

// ToDo2
PROVIDED_TEST("insert") {
    vector<int> intVec;

    for (int i = 12; i > 0; i--) {
        auto pos = intVec.insert(intVec.begin(), i);
        int offset = pos - intVec.begin();
        EXPECT_EQUAL(offset, 0);  // check return value
    }

    EXPECT_EQUAL(intVec.size(), 12);

    int val = 1;
    for (auto itr = intVec.begin(); itr < intVec.end(); ++itr) {
        EXPECT_EQUAL(*itr, val++);  // check elements
    }
}

PROVIDED_TEST("at/front/back") {
    vector<int> intVec(3, 0);
    EXPECT_EQUAL(intVec.at(1), 0);
    intVec.at(1) = 2;
    EXPECT_EQUAL(intVec.at(1), 2);
    EXPECT_ERROR(intVec.at(5));
    EXPECT_EQUAL(intVec.front(), 0);
    EXPECT_EQUAL(intVec.back(), 0);
}

PROVIDED_TEST("clear") {
    vector<int> intVec(5, 5);
    intVec.clear();
    EXPECT_EQUAL(intVec.size(), 0);
}

PROVIDED_TEST("erase") {
    vector<int> intVec(9, 2);
    auto pos = intVec.erase(intVec.begin());  // delete the first element
    EXPECT_EQUAL(intVec.size(), 8);
    EXPECT_EQUAL(pos - intVec.begin(), 0);  // check return value

    pos = intVec.erase(intVec.end() - 1);
    EXPECT_EQUAL(pos - intVec.begin(), 7);

    pos = intVec.erase(intVec.begin() + 5);
    EXPECT_EQUAL(pos - intVec.begin(), 5);
}

PROVIDED_TEST("push_back/pop_back") {
    vector<int> intVec;
    for (int i = 0; i < 9; i++) {
        intVec.push_back(i);
    }

    int val = 0;
    for (auto itr = intVec.begin(); itr < intVec.end(); ++itr) {
        EXPECT_EQUAL(*itr, val++);  // check elements
    }

    for (int i = 0; i < 9; i++) {
        intVec.pop_back();
        EXPECT_EQUAL(intVec.size(), 8 - i);
    }
}
