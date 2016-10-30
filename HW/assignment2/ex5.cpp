/* ECE373
 * Filename: ex5.cpp
 *
 * Problem: Define enumeration for associating numbers with colors. Then read 
 * typed numbers from the user and make a case statement that uses the 
 * enumeration to print the associated colors.
 *
 * 0=red
 * 1=yellow
 * 2=orange
 * 3=green
 * 4=blue
 * 5=purple
 *
 * All other numbers should print out as brown.
 */

#include <iostream> 
#include <stdlib.h>

using namespace std;

// enumeration usually is often placed in the .h file
/* write the enumeration of the colors here*/

int main()
{
  int val;

  while (true) {
	cout << "Type a number to find out its color:";
	cin >> val;
	if (cin.fail())
		exit(0);

	/*write the case statement to print the correct color*/
	switch(val)
	{
	case 0 : 
 		cout << "red" << endl;
		break;
	case 1 : 
		cout << "yellow" << endl;
		break;
	case 2 : 
		cout << "orange" << endl;
		break;
	case 3 : 
		cout << "green" << endl;
		break;
	case 4 : 
		cout << "blue" << endl;
		break;
	case 5 : 
		cout << "purple" << endl;
		break;
    	default: cout << "brown" << endl;
        }
   }
}
