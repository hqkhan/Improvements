#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shapes.h"

class Circle : public Shapes
{
public:
	Circle(float r)
	{
		r_ = r;
	}
	~Circle() {}

	float area() { return 2.0*3.141*r_; }

private:
	float r_;
};

#endif