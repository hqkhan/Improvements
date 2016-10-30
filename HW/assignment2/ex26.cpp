/* 
 * Filename: ex26.cpp
 *
 * The following program has a segmentation fault.  
 * Fix it using GDB by adding a single line of code to produce the 
 * following output:
 *
 * Val1 = 12
 * Val2 = 40
 * Val3 = 23
 * Val4 = 3
 *
 */

#include <iostream>
#include <string>

using namespace std;

int *p1, *p2, *p3, *p4;

int main () {
  int val1 = 5, val2 = 15, val3 = 20, val4 = 40;

  val1 = 6;
  p1 = &val1;
  *p1 = 8;      
  p3 = p2;
  p3 = &val4;
  *p1 = 12;
  *p3 = 20;
  p4 = p2;
  p2 = &val2;
  p1 = p4; //this is the problem
  
  p1 = p3;

  p4 = &val3;
  p3 = p4;
  *p4 = 41;
  *p3 = *p2;
  val4 = *p3;
  *p1 = 3;
  *p2 = *p1;      
  p3 = &val4;
  val2 = val3+5;
  *p4 = val1;
  p1 = p2;
  *p4 = 23;        
  *p1 = 40;         

  cout << "Val1 = " << val1 << endl;
  cout << "Val2 = " << val2 << endl;
  cout << "Val3 = " << val3 << endl;
  cout << "Val4 = " << val4 << endl;


  return 0;
}

