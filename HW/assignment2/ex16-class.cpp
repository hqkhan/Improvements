/* ECE373
 * Programming C++
 * Filename: ex16-class.cpp
 *
 */

#include <iostream>
#include "ex16-class.h"
#include <math.h>

using namespace std;


CRectangle::CRectangle(int x, int y) {
	// initialize the x and y in the constructor
	valX=x;
	valY=y;
	diagonal=sqrt(x*x+y*y);
}

CRectangle::CRectangle(void) {	// polymorphism two constructor functions
    // initialize the x and y in the constructor
    valX=5;
    valY=8;
    diagonal=sqrt(valX*valX+valY*valY);
}

CRectangle::~CRectangle(void) {
	// printout the size in the destructor
	std::cout << "The Rectangle of size x=" << valX << " y=" << valY <<
		" has been destroyed." << endl;
}

void CRectangle::set_values(int x, int y) {
    valX=x;
    valY=y;
    diagonal=sqrt(x*x+y*y);
}

int CRectangle::area (void) {
	// print out the area of the rectangle
	return valX*valY;
}

