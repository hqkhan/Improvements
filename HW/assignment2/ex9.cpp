/* ECE373
 *
 * Problem: Modify the program to obtain the factorial.
 */
#include <iostream> 

using namespace std;

int multiplyRecursive(int val) {
	/* These are local variables.
	 * Each time the function is called, a new local instance of each
	 * variable is created.
	 */
	int result;
	int nextMultiply = val-1;

	if (val > 0) {
		/*Add the recursion here*/
		result = val*multiplyRecursive(nextMultiply);
	} else {
		result = 1;
	}

	return result;
}

int main() {
	int factorialNum;
	cout << "Enter a natural number:";
	cin >> factorialNum;
	while ( ! cin.fail()) {
		cout << factorialNum << "! = " <<  multiplyRecursive(factorialNum) << endl;
		cin >> factorialNum;
	}
}

