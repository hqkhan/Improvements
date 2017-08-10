#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shapes.h";

class Rectangle : public Shapes
{
public:
	Rectangle(float x, float y){
		x_ = x;
		y_ = y;
	}
	float area(){ return x_*y_; }

	~Rectangle() {}
private:
	float x_;
	float y_;


};

#endif