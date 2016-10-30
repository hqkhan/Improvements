/* 
 * Filename: gdb4.cpp
 *
 * Problem: The summation of numbers in the following program gives an incorrect result. Fix it. 
 */

#include <iostream>
#include "ex27.h"

using namespace std;

int main () {
	SumNumbers sumObject;
	int ii;

	// initial values
    for (ii=0; ii < ARRAYSIZE; ii++) {
        sumObject.numList[ii] = 0;
    }

	sumObject.numList[3] = 5;
	sumObject.numList[5] = 3;
	sumObject.numList[7] = 8;

	// add the numbers together
	sumObject.add_numbers(); 

	return 0;
}

void SumNumbers::add_numbers(void) {
	int ii;
	
	sum = 0;

	for (ii=0; ii < ARRAYSIZE; ii++) {
		sum = sum + numList[ii];
	}

	cout << "The sum of 5+3+8 =" << sum << endl;
}

