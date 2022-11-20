//File: main.cpp
//--------------

#include "simpio.h"
#include <cmath>
#include <iostream>
#include "Diamond.h"

int main() {
	int program = getInteger("Select your program(1, 2, 3, 4): ");

	int value = 0;
	if (program == 1){
		value = getInteger("Enter your own storey: ");
		printDiamond(value ? value : STOREY);
    }/*else if (program == 2){
		value = getInteger("Enter your own storey: "); 
		printPyramid(value ? value : STOREY);
	}else if (program == 3){
		value = getInteger("Enter your own storey: ");
		printTriangle(value ? value : STOREY); 
	}else if (program == 4){
		value = getInteger("Enter your own storey: ");
		printTriangle2(value ? value : STOREY);*/
	else{
        std::cout << "Sorry, you have to select the given program" << std::endl;
    }
	return 0;
}
