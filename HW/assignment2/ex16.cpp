/* ECE373
 * Programming C++
 * Filename: ex16.cpp
 *
 * Problem: Print out the required values, and after the program completes
 * delete the dynamically created objects. This is needed to clean up the
 * memory the program uses.
 */

#include <iostream> 
#include "ex16-class.h"

using namespace std;

int main()
{
  double diagonalVal;
  int areaOfRect;
  CRectangle *ptrRect;
  CRectangle *ptrRectArray;

  CRectangle rect(4,6); // declare an object of the class
  areaOfRect= rect.area();
  cout << "Area: " << areaOfRect << endl; // print the area of the rectangle
  diagonalVal= rect.diagonal;
  cout << "Diagonal: " << diagonalVal << endl; // print the area of the rectangle

  ptrRect = new CRectangle(6,9);
  ptrRectArray = new CRectangle[2]; //creating an array of 2 pointers
  ptrRectArray[1].set_values(7,8);

  
  areaOfRect= ptrRect->area();
  cout << "ptrRect Area: " << areaOfRect << endl; // print the area of the rectangle
  diagonalVal= ptrRectArray[1].diagonal;
  cout << "ptrRectArray[1] Diagonal: " << diagonalVal << endl; 

  /* When you create a new object and address it with a pointer.
   * You need to "delete" it after you are done, or the memory is not freed.
   * This generates a memory leak if not deleted.
   */
  delete [] ptrRectArray;
  delete ptrRect;
  return 0;
}

