#include "BankAccount.h"
#include "console.h"
#include "random.h"
#include "testing/SimpleTest.h"
#include <iostream>
using namespace std;
void structDemo();
void DynamicMemoDemo();
void classDemo();

int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

    // structDemo();
    // classDemo();

    return 0;
}

void structDemo() {
    struct Student {
        string name;
        int age;
    };

    Student s;
    cout << "必须显式初始化" << endl;
    cout << s.name << endl;
    cout << s.age << endl;

    cout << "没有检查机制" << endl;
    s.name = "小明";
    s.age = -5;
    cout << s.name << endl;
    cout << s.age << endl;
}

void classDemo() {
    class Student {
        // 默认私有
        string name;
        int age;
        // 访问需要定义接口
    public:
        void setName(string str) {
            name = str;
        }
        string getName() {
            return name;
        }
        void setAge(int val) {
            age = val;
        }
        int getAge() {
            return age;
        }
    };

    Student s;
    cout << "类的封装机制" << endl;
    s.setName("小明");
    cout << s.getName() << endl;
}

void DynamicMemoDemo() {
    int init_size = 10;
    int *data = new int[init_size];
    for (int i = 0; i < init_size; i++) {
        data[i] = randomInteger(0, 100);
    }
    delete[] data;
}

PROVIDED_TEST("DynamicMemoDemo") {
    TIME_OPERATION(10, DynamicMemoDemo());
}
