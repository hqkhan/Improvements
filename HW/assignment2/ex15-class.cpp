/* ECE373
 * Programming C++
 * Filename: ex15-class.cpp
 *
 */

#include <iostream>
#include "ex15-class.h"

using namespace std;

/*Declare all the needed functions here*/


// initialize the x and y in the constructor
CRectangle::CRectangle(int x, int y){
	valX=x;
	valY=y;
}

// printout the size in the destructor
CRectangle::~CRectangle(void){
	std::cout << "The Rectangle of size x=" << valX << " y=" << valY <<" has been destroyed." << endl;
}

// print out the area of the rectangle
int CRectangle::area(void){
	return valX*valY;
}

