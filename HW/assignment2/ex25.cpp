/* 
 * ECE373
 * Filename: ex25.cpp
 *
 * Problem: This program will throw an divide by zero error. Catch the error, and instead
 * provide the reason for the exception then exit gracefully.
 */

#include <iostream>
using namespace std;

int main ()
{
	int xx=50;
	int yy=0;
	int error=55;
	try
	{
		if (yy ==0) throw error;
		cout << xx/yy << endl;
	} catch (int& f) {
		cout<<"Exception Thrown - yy is zero and is used to divide a number."<<endl;
		cout << "Program Exiting Gracefully." << endl;
	}
}
