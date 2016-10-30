/* ECE373
 * Programming C++
 * Filename: ex17.cpp
 *
 * Problem: structs are similar to class objects in how you declare and
 * reference them. Declare the struct that is being used in the code. The
 * main differences from an object are: you cannot have functions in a struct,
 * and you cannot set private or protected variables.
 */

#include <iostream>
#include <stdlib.h>

using namespace std;


/* Declare a struct for rectangle that works with the code. 
 * At the same time as declaring the struct also declare the instance rectA.
 */
struct rectangle{
	int x;
	int y;
};

int main()
{
	rectangle* ptrRect;
	ptrRect = new rectangle;

	struct rectangle rectA;
	cout << "Enter x value:";
	cin >> rectA.x;
	if (cin.fail())
		exit(0);

	cout << "Enter y value:";
    cin >> rectA.y;
    if (cin.fail())
        exit(0);

	ptrRect->x = rectA.x + 3;
	ptrRect->y = rectA.y + 4;

	cout << "x:" << ptrRect->x <<" y:" << ptrRect->y << endl;

	cout << "You've got a working struct!" << endl;

	delete ptrRect;

}

