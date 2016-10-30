/* ECE373
 * Programming C++
 * Filename: ex19.cpp
 *
 * Problem: Pass an array of integers to the function.
 */

#include <iostream>

using namespace std;

#define ARRAY_SIZE 10

void printOutArray(int array[], int arraySize) {
    int ii;
    for (ii=0;ii<arraySize;ii++) {
        cout << "[" << array[ii] << "]";
    }
    cout << endl;
}

int main()
{
	int array[ARRAY_SIZE];
	int ii;

	for (ii=0;ii<ARRAY_SIZE;ii++) {
		array[ii] = ii*2+1;
	}

	printOutArray(array, ARRAY_SIZE);
}

