/* ECE373
 * Programming C++
 * Filename: ex15.cpp
 *
 * Problem: Declare all the functions of the class CRectangle in the 
 * 	file ex15-class.cpp. See ex15-class.h for the function prototypes. 
 */

#include <iostream> 
#include "ex15-class.h"

using namespace std;

int main()
{

  CRectangle rect(3,4); // declare an object of the class
  cout << "Area: " << rect.area() << endl; // print the area of the rectangle

  return 0;
}

