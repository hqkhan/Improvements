/* 
 * ECE373
 * Filename: ex22.cpp
 *
 * Problem: Use operator overloading to make the "+" of two complex numbers work in the code. Note that an example of
 * operator overloading for << is already shown. However, this is for the global case. You only want to create one
 * for the internal class case.
 */

#include <iostream>
#include <sstream>

using namespace std;

class Complex
{
    public:
        Complex(double re,double im) {
			real=re;
			imagine=im;
		};
		Complex Add(const Complex& secondArg);

		// allow for this external to the class functions to access internal variables
		friend ostream& operator<<(ostream &out, Complex c);
		friend Complex operator+(Complex firstArg, const Complex& secondArg);

    private:
        double real;
        double imagine;
};

Complex Complex::Add(const Complex& secondArg)
{
	double returnReal = real + secondArg.real;
	double returnImag = imagine + secondArg.imagine;
	return Complex( returnReal, returnImag);
}

// global declaration of function (non-class declaration)
// overloads the situation of "ostream << complexNumber"
ostream &operator<<(ostream &out, Complex c) {
	out << "Real: " << c.real << endl;
	out << "Imaginary: " << c.imagine << endl;
	return out;
}

Complex operator+(Complex firstArg, const Complex& secondArg)
{	
	double realval = firstArg.real + secondArg.real;
	double imagval = firstArg.imagine + secondArg.imagine;
	return Complex(realval,imagval);
}

int main()
{
	Complex var1 (4,7);
	Complex var2 (3,6);

// This is the previous way the result was calculated
//	Complex result = var1.Add(var2);

	Complex result = var1 + var2;

	cout << result;
}

