#include "Rectangle.h"
#include "Circle.h"
#include "Shapes.h"
#include <iostream>
#include <vector>

int main() {

	//Rectangle rect1 = Rectangle(1.0, 1.0);
	Rectangle rect1 = Rectangle(1.0, 1.0);
	Rectangle rect2 = Rectangle(2.0, 2.0);
	Circle circle1 = Circle(1.0);

	std::vector<Rectangle> r;
	r.push_back(rect1);
	r.push_back(rect2);

	std::vector<Rectangle>::iterator it;
	for (it = r.begin(); it != r.end(); ++it)
	{
		float area = it->area();
		std::cout << "area =" << area << std::endl;
	}

	double s[10];
	
	return 0;
}