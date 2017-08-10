#ifndef COVARIANCE_H
#define COVARIANCE_H

#include <cstring>

class Covariance
{
public:
	Covariance(float** cov)
	{
		int i, j;

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				cov_mat[i][j] = cov[i][j];
			}
		}
		
	}
	~Covariance(){}

private:
	float cov_mat[4][4];


};
#endif 