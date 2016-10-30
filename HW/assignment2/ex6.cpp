/* ECE373
 * Filename: ex6.cpp
 *
 * Problem: Declare all the variables correctly.
 */
#include <iostream> 

using namespace std;

int main()
{
	/* define the variables here */

	double var1 = 5.135;
	double var2 = var1*2523242342533/3559/3571/3557;

	int var3 = 5024142;
	long double var4 = -9223372036854775807;
	long double var5 = 7223372036854775807;
	var5 = var5*2;
	char var6 = '7';
	char var7[] = "Success";

	/* replace X with the right precision below to match the output */
	cout.precision(4);
	cout << "var1:" << var1;
	cout.precision(7);
	cout << " var2:" << var2 << endl; 
	cout.precision(30);

	cout << "var3:"	<< var3;
	cout << " var4:" << var4;
	cout << " var5:" << var5 << endl;

	cout << "var6:" << var6 << " var7:" << var7 <<endl;
}

