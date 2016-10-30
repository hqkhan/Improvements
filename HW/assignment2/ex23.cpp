/* 
 * ECE373
 * Filename: ex23.cpp
 *
 * Problem: Create a template class called ArrayOf... to replace ArrayOfInt 
 * and ArrayOfFloat. Then uncomment the lines for ArrayOfString.
 */

#include <iostream>
#include <string>

using namespace std;

template <class example>
class ArrayOf
{
	public:
		ArrayOf<example>(void){};
		example returnElement(size_t index);
		void setElement(size_t index,example value);
		void setAll(example value);
	private:
		example array[50];
};

template <class example>
example ArrayOf<example>::returnElement (size_t index) {
	return array[index];
}

template <class example>
void ArrayOf<example>::setElement(size_t index, example value) {
	array[index] = value;	
}

template <class example>
void ArrayOf<example>::setAll(example value) {
	for (int ii=0;ii<50;ii++)
		array[ii]=value;
}



/* This should be in a header file */
class ArrayOfInt
{
	public:
		ArrayOfInt(void) {};
		int returnElement(size_t index);
		void setElement(size_t index,int value);
		void setAll(int value);
	private:
		int array[50];
};
/* The above should have been in a header file */

int ArrayOfInt::returnElement (size_t index) {
	return array[index];
}

void ArrayOfInt::setElement(size_t index, int value) {
	array[index] = value;	
}

void ArrayOfInt::setAll(int value) {
	for (int ii=0;ii<50;ii++)
		array[ii]=value;
}

/* This should be in a header file */
class ArrayOfFloat
{
    public:
        ArrayOfFloat(void) {};
        float returnElement(size_t index);
        void setElement(size_t index,float value);
        void setAll(float value);
    private:
        float array[50];
};
/* The above should have been in a header file */

float ArrayOfFloat::returnElement (size_t index) {
    return array[index];
}

void ArrayOfFloat::setElement(size_t index, float value) {
    array[index] = value;
}

void ArrayOfFloat::setAll(float value) {
    for (size_t ii=0;ii<50;ii++)
        array[ii]=value;
}

int main()
{
	ArrayOfInt object1;
	ArrayOfFloat object2;
	 ArrayOf<string> object3;

	object1.setAll(5);
	object1.setElement(10,15);

    object2.setAll(3.46);
    object2.setElement(10,14.46);

     object3.setAll("Default String");
     object3.setElement(15,"This is the 16th Element");

	cout << "Obtaining Element 8 of Object1: " << object1.returnElement(7) << endl;
	cout << "Obtaining Element 11 of Object2: " << object2.returnElement(10) << endl;
	 cout << "Obtaining Element 16 of Object3: " << object3.returnElement(15) << endl;
}

