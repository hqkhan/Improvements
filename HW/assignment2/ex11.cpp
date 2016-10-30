/* ECE373
 * Filename: ex11.cpp
 *
 * Problem: The function uses recursion, but incorrectly modifies a local 
 * variable that gets overwritten each time. Change the code to use a 
 * static variable to obtain the correct result from the function.
 *
 * Note: In many cases, using global variables can be replaced with 
 * return values and arguments. This is just to teach you how global
 * and local variables work.
 */
#include <iostream> 

using namespace std;

int calculation (int inputValue) {
       static int counter = 0;
	if (inputValue > 0) {
		inputValue += calculation(inputValue/2);
    }
	counter++;
	inputValue += 5;
	cout << "Number of calls (" << counter << "): inputValue = " \
		<< inputValue << endl;
	return inputValue;
}


int main()
{
	int inputValue = 8;
	cout << inputValue << endl;
	inputValue = calculation(inputValue);
	cout << inputValue << endl;
}

