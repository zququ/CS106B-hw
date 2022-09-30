/**
 * @file PowersOfTwo.cpp
 * @brief This program generates a list of the powers of 2
 * up to an exponent limit entered by the user.
 */

#include "console.h"
#include "power_of_two.h"
#include "simpio.h" // for getInteger
#include <iostream>

using namespace std;

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
