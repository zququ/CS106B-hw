#include <iostream>
using namespace std;

bool isEven(int value);
int doubleValue(int x);

// buggy version
int average(int a, int b) {
    double sum = a + b;
    return sum / 2;
}

int main() {
    // -----------------------------------------------
    std::cout << "变量" << std::endl;
    int result;
    result = 0;
    std::cout << result << std::endl;
    // or
    int result2 = 0;
    result = 3;
    std::cout << result << "\n" << result2 << std::endl;

    // 整型范围
    int val = 2147483647;
    val = val + 1;

    std::cout << val << std::endl;

    // 复合类型
    struct Student {
        string name; // these are called fields
        int age;
        string city; // separate these by semicolons
    };

    Student s;
    s.name = "小明"; // use . to access fields
    s.age = 28;
    s.city= "北京";

    // or
    // Student s2 = {"小明", "北京", 28}; // buggy
    Student s3 = {"小明", 28, "北京"};

    //    Two ways to run recycling
    //    -------------------------
    //    for (int i = 0; i < 10; i++) {
    //        cout << "for" << endl;
    //    }
    //    cout << i;

    //    int j = 0;
    //    while(j < 10) {
    //        cout << "while" << endl;
    //        j++;
    //    }
    //    cout << j;
    //
    //    Most time, "for" recycling may be
    //    better than "while" recycling, because
    //    while will left the "j = 0" out of the
    //    recycling.

    double sum = 0.0, term = 0.5;
    int count = 0;
    while (sum != sum + term) {
        // while (0 != term) {
        sum += term;
        term /= 2;
        count++;
    }
    cout << "The sum is " << sum << endl;
    cout << "The num of loop is " << count << endl;

    // pass by value
    int myValue = 5;
    int result3 = doubleValue(myValue);
    cout << "myValue: " << myValue << " ";
    cout << "result: " << result3 << endl;

    // average
    cout << average(1, 120) << endl;

    return 0;
}

bool isEven(int value) {
    return value % 2 == 0 ? true : false;
}


int doubleValue(int x) {
    x *= 2;
    return x;
}
