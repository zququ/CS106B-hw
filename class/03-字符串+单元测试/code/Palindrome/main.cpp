#include "console.h"
#include "testing/SimpleTest.h" // for testing
#include <iostream>
using namespace std;

int main() {
    // for testing
    if (runSimpleTests(SELECTED_TESTS))
        return 0;

    return 0;
}
