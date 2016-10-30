/* ECE373
 * Filename: ex4.cpp
 *
 * Problem: Make a while loop that loops until the user types y. Then make a
 *  for loop that will count from 1 to 5.
 */
#include <iostream> 

using namespace std;

int main()
{
	string inputVal;
	int ii;

	cout << "Do you want to continue?:";
	cin >> inputVal;

	/* http://www.cplusplus.com/reference/string/string/
	* inputVal is a String, so you can't do a direct conditional
	* statement with stringVar = stringVar2.
	* The above gives a reference for some of the String functions
	* in the String class.
	*/

	/*Modify to add a while loop*/
	while(true){
		if (inputVal.compare("y") != 0) {
			cout << "Do you want to continue?:";
			cin >> inputVal;
		}
		else break;
	}

	/*Modify to add a for loop*/
		
		for(ii = 1;ii<=5;ii++) cout << ii << endl;
	
}

