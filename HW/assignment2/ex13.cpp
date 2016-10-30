/* ECE373
 * Programming C++
 * Filename: ex13.cpp
 *
 * Problem: Call the ex13-funcs.cpp functions to obtain two random numbers from
 * the external function and then use the multiply them using the external
 * function. The random numbers require an input initializer. You will need
 * to define the ex13-funcs header file, and #include it in the file you want
 * to use the functions in.
 */

#include <iostream>
#include <stdlib.h>
/*Add the include file*/
#include "ex13-funcs.h"

using namespace std;

int main()
{
	int input, val1, val2;
	long multipliedResult;

	while (true) {
		cout << "Type first initialize number:";
	    cin >> input;
	    if (cin.fail())
			exit(0);

		/* Add the get random number function*/
		val1 = getRandNumber(input);


        cout << "Type second initialize number:";
        cin >> input;
        if (cin.fail())
            exit(0);

		/* Add the get random number function again*/
		val2 = getRandNumber(input);


		/* Add the multiply two numbers together function*/
		multipliedResult = multiply(val1, val2);

		cout << "Multiplication of:" << val1 << " * " << val2 << endl;
		cout << "Result:" << multipliedResult << endl;
	}
}

