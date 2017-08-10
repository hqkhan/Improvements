#ifndef STATE_UPD_H
#define STATE_UPD_H


class State_upd
{
public:
	State_upd(float** state_vec)
	{
		int i, j;

		state = state_vec;
		
	}
	~State_upd(){}

	float** get_state(){ return state; }
	


private:
	float** state;
};
#endif