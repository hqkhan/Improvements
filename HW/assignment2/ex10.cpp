/* ECE373
 * Filename: ex10.cpp
 *
 * Problem: The function does nothing due to using local variables. 
 * Change the code to use a global variable to obtain a result from the function.
 */
#include <iostream> 

using namespace std;

void calculation () {
	inputValue += 5;
}
int inputValue;
int main()
{
	cout << inputValue << endl;
	calculation();
	cout << inputValue << endl;
}

