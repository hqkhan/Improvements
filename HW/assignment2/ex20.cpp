/* 
 * ECE373
 * Filename: ex20.cpp
 *
 * Problem: This program is storing numbers in strings. It should be storing
 * numbers in integers. Change the number being used from xxx and yyy to x and 
 * y. In C++ to encode integers into a string the best way is to use 
 * ostringstream. Use ostringstream to encode the new numbers.
 */

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	ostringstream stringtemp;
	string str1;
	int x=240;
	int y=40;
	string xxx="5";
	string yyy="10";

	stringtemp<<"The first number is x="<<x<<", the second number is y="<<y<<".";
	str1 = stringtemp.str();

	//str1.assign("The first number is x=");
	//str1.append(x);	
	//str1.append(", the second number is y=");
	//str1.append(y);
	//str1.append(".");

	cout << str1 << endl;
}

