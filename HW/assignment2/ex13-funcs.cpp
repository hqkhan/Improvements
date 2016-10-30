/* ECE373
 * Programming C++
 * Filename: ex13-funcs.cpp
 *
 */
#include <time.h>
#include <stdlib.h>

int getRandNumber(int input) {
	srand(input);
	return rand() % 50 + 1;
}

long multiply(int val1, int val2) {
	return val1*val2;
}


