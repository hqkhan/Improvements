/* ECE373
 * Filename: ex3.cpp
 *
 * Problem: Read two marks input by the user between 0 to 100 input.
 * When both marks are above 80 print A
 * When both marks are above or equal to 60 print B, but both marks aren't 
 * above 80. When at least one mark is above 50 print C.  Otherwise in all other cases print D.
 */

#include <iostream> 
#include <stdlib.h>

using namespace std;

int main()
{
	int val = 1;
	int val2 = 1;

	while (true) {
		cout << "Enter First Mark:";
		cin >> val;
		if (cin.fail())
			exit(0);
		cout << "Enter Second Mark:";
		cin >> val2;
        if (cin.fail())
            exit(0);
	//	cout<<val<<" "<<val2<<" ";
		/*Modify the following to get correct behaviour*/
		if (val>80 && val2>80) {cout << "A" << endl;}
		else if (val>=60 && val2>=60) {
			if(val<=80 || val2<=80)cout << "B" << endl;
		       
			}
		     else if (val>50 || val2>50) cout << "C" << endl;
			  else cout << "D" << endl;

	}
}

