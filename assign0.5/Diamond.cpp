#include <cmath>
#include <iostream>

//@brief printDiamond
//@param storey

void printDiamond(int storey){
	for (int i = 1 - storey; i <= storey; i++){
		for (int j = 1 - storey; j <= storey - 1; j++){
			int sum = abs(i) + abs(j);
			if (sum <= storey){
				std::cout << "*";
			}else{
				std::cout << " ";
			}
	}
		std::cout << std::endl;
}
}

void print()
