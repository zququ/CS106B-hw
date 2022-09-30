/**
 * File : main.cpp
 * -- -- -- -- -- -- --
 * A program prints a triangle with the storey is what
 * you provide.If no input, print six storey as default.
 */

#include "console.h"
#include "simpio.h"
#include <cmath>
#include <iostream>
using namespace std;

/* Constant Variable */

const int STOREY = 6;

/* Function Prototype */

void printDiamond(int storey);
void printPyramid(int storey);
void printTriangle(int storey);
void printTriangle2(int storey);

/* Main Entry */

int main() {
    int program = getInteger("Select your program(1, 2, 3, 4): ");

    int value = 0;
    if (program == 1) {
        value = getInteger("Enter your own storey: ");
        printDiamond(value ? value : STOREY);
    } else if (program == 2) {
        value = getInteger("Enter your own storey: ");
        printPyramid(value ? value : STOREY);
    } else if (program == 3) {
        value = getInteger("Enter your own storey: ");
        printTriangle(value ? value : STOREY);
    } else if (program == 4) {
        value = getInteger("Enter your own storey: ");
        printTriangle2(value ? value : STOREY);
    } else {
        cout << "Sorry, you have to select the given program." << endl;
    }

    return 0;
}

/* Function Implementation */

/**
 * @brief printDiamond
 * @param storey
 */
void printDiamond(int storey) {
    for (int i = 1 - storey; i <= storey; i++) {
        for (int j = 1 - storey; j <= storey; j++) {
            int sum = abs(i) + abs(j);
            if (sum <= storey - 1) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

/**
 * @brief printPyramid
 * @param storey
 */
void printPyramid(int storey) {
    for (int i = storey; i >= 0; i--) {
        for (int j = -storey; j <= storey; j++) {
            int sum = abs(i) + abs(j);
            if (sum <= storey) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

/**
 * @brief printTriangle
 * @param storey
 */
void printTriangle(int storey) {
    for (int i = storey - 1; i >= 0; i--) {
        for (int j = 1 - storey; j < storey; j++) {
            int sum = abs(i) + abs(j);
            if (sum <= storey && sum == (storey - 1)) {
                cout << "*";
            } else if (sum <= storey && sum % 2 == (storey - 1) % 2 && i == 0) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void printTriangle2(int storey) {
    for (int i = storey - 1; i >= 0; i--) {
        for (int j = 1 - storey; j < storey; j++) {
            int sum = abs(i) + abs(j);
            if (sum <= storey && sum == (storey - 1)) {
                cout << storey - i;
            } else if (sum <= storey && sum % 2 == (storey - 1) % 2 && i == 0) {
                cout << storey - i;
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}
