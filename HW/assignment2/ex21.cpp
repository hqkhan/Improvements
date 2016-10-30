/* 
 * ECE373
 * Filename: ex21.cpp
 *
 * Problem: Create a DerivedClass that inherits from BaseClass and overloads the
 * method doOperation. The new doOperation should print out 
 * "Multiply(a,b)+Sum(a,b): " followed by the result.
 */

#include <iostream>
using namespace std;

/* This should normally be placed in a header file */
class BaseClass {
public:
  void doOperation(int a, int b);
  int multiply(int a, int b);
  int addition(int a, int b);
};

/* End the section that should have been placed in a header file */

void BaseClass::doOperation(int a, int b) {
	cout << "Multiply: " << multiply(a, b) << " Add: " << addition(a,b) << endl;
}
int BaseClass::multiply(int a, int b){
 	return a*b;
}
int BaseClass::addition(int a, int b){
	return a+b;
}

class DerivedClass: public BaseClass
{
	public:
		int doOperation(int a, int b)
		{
			cout << "Multiply(a,b)+Sum(a,b): " << multiply(a, b) + addition(a,b) << endl;
		}
};

int main()
{
	BaseClass objectName;
	DerivedClass objectName2;

	objectName.doOperation(18,5);
	objectName2.doOperation(18,5);
}

