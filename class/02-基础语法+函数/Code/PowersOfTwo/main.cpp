/**
 * @file PowersOfTwo.cpp
 * @brief This program generates a list of the powers of 2
 * up to an exponent limit entered by the user.
 */


#include <iostream>
#include "console.h"
#include "simpio.h" // for getInteger

using namespace std;

/* Function Prototype */
int raiseToPower(int n, int k);

/* Main Entry */
int main() {
  cout << "This program lists powers of two." << endl;

  // Get input from user
  int limit = getInteger("Enter exponent limit: ");
  // Do something ..
  for (int i = 0; i <= limit; i++) {
    cout << "2 to the " << i << " = " << raiseToPower(2, i) << endl;
  }

  return 0;
}

/**
 * @brief raiseToPower
 * Usage: int p = raiseToPower(n, k);
 * ----------------------------------
 * Return the integer n raised to the kth power.
 */
int raiseToPower(int n, int k) {
  int result = 1;
  for (size_t i = 0; i < k; i++) {
    result *= n;
  }
  return result;
}
