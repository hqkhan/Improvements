/* 
 * ECE373
 * Filename: ex24.cpp
 *
 * Problem: Use the standard template library <list> to make a list and sort the names. 
 * Then print out the names from the list. 
 * http://www.cplusplus.com/reference/stl/list/list/
 */

#include <iostream>
#include <list>
#include <string>
#include <cctype>
using namespace std;

int main ()
{
  list<string> myList;
  list<string>::iterator it;
  
  myList.push_back("Eve");
  myList.push_back("David");
  myList.push_back("Adam");
  myList.push_back("Jacob");
  myList.sort(); 
  cout << "The sorted names are:";
  for(it=myList.begin();it!=myList.end();++it)cout<<" "<<*it; 
  cout<<endl;
  return 0;
}
