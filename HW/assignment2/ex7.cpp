/* ECE373
 * Filename: ex7.cpp
 *
 * Problem: Type cast the division operation so it is performed correctly
 */
#include <iostream> 

using namespace std;

int main()
{
	int A,B;
	double C;

	cout << "A common mistake is dividing two integer numbers together, then getting an integer when you want a decimal number."<< endl;
	A=7;
	B=2;

	/*use type casting to fix this calculation*/
	C=double(A)/double(B);

	cout << A << " divided by " << B << " equals " << C << "." << endl;
}


