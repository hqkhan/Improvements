/* ECE373
 * Programming C++
 * Filename: ex14.cpp
 *
 * Problem: Replace the ? symbol with either a * or a & or nothing.
 * To get the result val1=12 and val2=40.
 */

#include <iostream> 

using namespace std;

int main()
{
  int val1 = 5, val2 = 15;
  int * p1, * p2;

  p1 = &val1;		 // p1 = address of val1
  p2 = &val2;		 // p2 = address of val2
  *p1 = 12;          // value pointed by p1 = 12
  *p2 = *p1;         // value pointed by p2 = value pointed by p1
  p1 = p2;           // p1 = p2 (value of pointer is copied)
  *p1 = 40;          // value pointed by p1 = 40
  
  cout << "val1 is " << val1 << endl;
  cout << "val2 is " << val2 << endl;

  return 0;
}
