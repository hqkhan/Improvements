#ifndef TRUTH_H
#define TRUTH_H

class Truth{
	public:
		Truth(float x1, float y1, float xvel1, float yvel1){
			x = x1;
			y = y1;
			xvel = xvel1;
			yvel = yvel1;
		}
		~Truth(){}

		float x_pos(){ return x; }
		float y_pos(){ return y; }
		float vx(){ return xvel; }
		float vy(){ return yvel; }

	private:
		float x;
		float y;
		float xvel;
		float yvel;

};

#endif