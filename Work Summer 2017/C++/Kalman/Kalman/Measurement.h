#ifndef MEASUREMENT_H
#define MEASUREMENT_H

class Measurement{

public:
	Measurement(int x1, int y1){
		x = x1;
		y = y1;
	}
	~Measurement(){}
	
	float x_pos(){ return float(x); }
	float y_pos(){ return float(y); }

private:
	int x;
	int y;

};

#endif