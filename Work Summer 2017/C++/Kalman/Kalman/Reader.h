#ifndef READER_H
#define READER_H

#include <vector> //for vectors
#include <string> //for strings when reading in truth/measurements
#include <fstream>
#include <sstream>
#include <cmath> //pow function
#include <assert.h> //for assertions
#include <cstdlib> //for exit
#include "Measurement.h"
#include "Truth.h"
#include "Covariance.h"
#include "State_upd.h"

#include <typeinfo>

class Reader
{
	public:
		Reader(std::ifstream* measurement_filename, std::ifstream* truth_filename)
		{
			std::string vec, token;
			int i, x, y;

			if (!measurement_filename->is_open()) std::cout << "Error while trying to open measurement file" << std::endl;

			while (!measurement_filename->eof()) //good function looks how long the file is, can also do EOF
			{
				std::getline(*measurement_filename, vec);
				std::istringstream ss(vec);
				
				std::getline(ss, token, ',');
				//std::cout << typeid(token).name() << std::endl;
				x = std::stoi(token);
				std::getline(ss, token, '\n');
				y = std::stoi(token);
				
				Measurement state_measure = Measurement(x, y);
				m.push_back(state_measure);
			}

			if (!truth_filename->is_open()) std::cout << "Error while trying to open truth file" << std::endl;

			float xt, yt, xvel, yvel;
			while (!truth_filename->eof()) //good function looks how long the file is, can also do EOF
			{
				std::getline(*truth_filename, vec);
				std::istringstream ss(vec);

				std::getline(ss, token, ',');
				xt = std::stoi(token);
				std::getline(ss, token, ',');
				yt = std::stoi(token);
				std::getline(ss, token, ',');
				xvel = std::stoi(token);
				std::getline(ss, token, '\n');
				yvel = std::stoi(token);

				Truth state_truth = Truth(xt, yt, xvel, yvel);
				t.push_back(state_truth);
			}

			Kalman_Filter();
		}
		~Reader(){} //deconstructor

		std::vector<Measurement>* measurement_vec_loc(){ return &m; }
		std::vector<Truth>* truth_vec_loc(){ return &t; }
		
		void Kalman_Filter()
		{
			int i, j;
			float process_noise = 1.0;
			
			float** C = create_matrix(2, 4);

			for (i = 0; i < 2; i++)
			{
				for (j = 0; j < 4; j++)
					C[i][j] = 0;
			}
		
			C[0][0] = 1;
			C[1][1] = 1;
			print_matrix(multiply(C, transpose(C, 2, 4), 2, 4, 4, 2), 2, 2);
			Forward_pass(process_noise, C);
			write_to_file();

		}

		void write_to_file()
		{
			std::ofstream outf("C:/Users/hka0211/Documents/Practice/C++/output.csv");

			if (!outf) std::cout << "File could not be opened" << std::endl;

			std::vector<State_upd>::iterator it;
			for (it = s.begin(); it != s.end(); it++)
			{
				outf << (it->get_state())[0][0] << ',' << (it->get_state())[1][0] << ',' << (it->get_state())[2][0] << ',' << (it->get_state())[3][0] << ',';
				outf << std::endl;
			}
		}

		void Forward_pass(float process_noise, float** C)
		{
			int i, j, delta_t = 1;
			float R = 1.0 / 12.0; //measurement covariance for high resolution -> change to (size_of_block**2)/12 if necessary
			float cov_measure_test[4][4] = { R, 0, 0, 0, 0, R, 0, 0, 0, 0, 0, 0.01, 0, 0, 0, 0.01 };
			float F_test[4][4]= { 1, 0, delta_t, 0, 0, 1, 0, delta_t, 0, 0, 1, 0, 0, 0, 0, 1 };
			float Q_test[4][4] = { process_noise*pow(delta_t, 3) / 3.0, 0, process_noise*pow(delta_t, 2) / 2.0, 0, 0, process_noise*pow(delta_t, 3) / 3.0, 0, process_noise*pow(delta_t, 2) / 2.0, process_noise*pow(delta_t, 2) / 2.0, 0, process_noise*delta_t, 0, 0, process_noise*pow(delta_t, 3) / 2.0, 0, process_noise*delta_t };
			
			float** R_mat = create_matrix(2, 2);
			R_mat[0][0] = R;
			R_mat[0][1] = 0;
			R_mat[1][0] = 0;
			R_mat[1][1] = R;

			float** F = create_matrix(4, 4);

			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 4; j++)
					F[i][j] = F_test[i][j];
			}

			float** Q = create_matrix(4, 4);

			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 4; j++)
					Q[i][j] = Q_test[i][j];
			}

			float** cov_measure = create_matrix(4, 4);

			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 4; j++)
					cov_measure[i][j] = cov_measure_test[i][j];
			}

			//appending first covariance and state vectors which were the same as the measurement
			//We need to start with SOMETHING therefore we take exactly the measurements and filter forward
			Covariance cov = Covariance(cov_measure);
			c.push_back(cov);
			Measurement first = m.front();
			float** x_old = create_matrix(4, 1);

			x_old[0][0] = first.x_pos();
			x_old[1][0] = first.y_pos();
			x_old[2][0] = 0;
			x_old[3][0] = 0;
			
			State_upd state = State_upd(x_old);
			s.push_back(state);

			m.erase(m.begin()); //removing the first measurement
			std::vector<Measurement>::iterator it;

			for (it = m.begin(); it != m.end(); it++) //going from beginning of measurements to end of measurements
			{
				//predict
				float** x_new = multiply(F, x_old, 4, 4, 4, 1);
				float** cov_new = addition(multiply(F, multiply(cov_measure, transpose(F, 4, 4), 4, 4, 4, 4), 4, 4, 4, 4), Q, 4, 4, 4, 4);

				//update
				float** kalman_gain = multiply(multiply(cov_new, transpose(C, 2, 4), 4, 4, 4, 2), inverse(addition(multiply(C, multiply(cov_new, transpose(C, 2, 4), 4, 4, 4, 2), 2, 4, 4, 2), R_mat, 2, 2, 2, 2), 2), 4, 2, 2, 2);
				float** measurement = create_matrix(2, 1);
				measurement[0][0] = it->x_pos();
				measurement[1][0] = it->y_pos();
				float** x_upd = addition(x_new, multiply(kalman_gain, subtract(measurement, multiply(C, x_new, 2, 4, 4, 1), 2, 1, 2, 1), 4, 2, 2, 1), 4, 1, 4, 1);
				float** cov_upd = subtract(cov_new, multiply(kalman_gain, multiply(C, cov_new, 2, 4, 4, 4), 4, 2, 2, 4), 4, 4, 4, 4);

				State_upd state = State_upd(x_upd);
				Covariance cov = Covariance(cov_upd);
				s.push_back(state);
				c.push_back(cov);

				x_old = copy_matrix(x_new, x_old, 4, 1);
				cov_measure = copy_matrix(cov_upd, cov_measure, 4, 4);			
			}

			std::cin.get();
			//release all dynamically allocated memory here
			release_memory(cov_measure, 4, 4);
			release_memory(C, 2, 4);
			release_memory(Q, 4, 4);
			release_memory(F, 4, 4);
			release_memory(R_mat, 2, 2);

		}
		
		void print_matrix(float** matrix, int row, int col)
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
					std::cout << matrix[i][j] << ' ';
				std::cout<<std::endl;
			}
		}
		void release_memory(float** matrix, int row, int col)
		{
			for (int i = 0; i < row; i++)
				delete[] matrix[i];
		}

		float** copy_matrix(float** first_arg, float** second_arg, int x, int y)
		{
			for (int i = 0; i < x; i++)
			{
				for (int j = 0; j < y; j++)				
					second_arg[i][j] = first_arg[i][j];			
			}

			return second_arg;
		}

		float** create_matrix(int row, int col)
		{
			float** result = new float*[row];
			for (int i = 0; i < row; i++)
				result[i] = new float[col];

			return result;
		}

		float determinant_new(float** first_arg)
		{
			return (first_arg[0][0] * first_arg[1][1]) - (first_arg[0][1] * first_arg[1][0]);
		}

		float** inverse(float** first_arg, int max_dim)
		{
			float det = determinant_new(first_arg);
			float** adj = create_matrix(max_dim, max_dim);
			int sign = 1;
			
			adj[0][0] = first_arg[1][1];
			adj[0][1] = -first_arg[0][1];
			adj[1][0] = -first_arg[1][0];
			adj[1][1] = first_arg[0][0];

			/*adjugate
			for (int i = 0; i < max_dim; i++)
			{
				for (int j = 0; j < max_dim; j++)
				{
					copy_of_first_arg[i][j] = (1.0/det)*sign*first_arg[i][j];
					sign = -sign;
				}
			}*/

			return adj;
		}

		void shrink(float** matrix, float** fill_up, int row, int col, int max_dim)
		{
			int i, j, p=0, q=0;

			for (i = 0; i < max_dim; i++)
			{
				for (j = 0; j < max_dim; j++)
				{
					if (j != col && i != row) //if not in the same row or column, place in temp
						fill_up[p][q++] = matrix[i][j];
					
					
					if (q == max_dim-1) //filled up a row
					{
						q = 0; //reset the column
						p++; //increase row counter
					}
				}
			}
		}

		float determinant(float** first_arg, int max_dim) // initially assuming to be a square matrix and row start is low and row end must be high
		{
			
			float det=0;
			
			if (max_dim == 1) //it is a 2x2 
				return first_arg[0][0];
				//return first_arg[0][0] * first_arg[1][1] - first_arg[0][1] * first_arg[1][0];

			int sign = 1;
			float** cofactor_mat = create_matrix(max_dim, max_dim);

			for (int i = 0; i < max_dim; i++)
			{
				
				shrink(first_arg, cofactor_mat, 0, i, max_dim);
				det += sign * first_arg[0][i] * determinant(cofactor_mat, max_dim - 1);
				sign = -sign;

			}

			return det;
		}

		float** addition(float** first_arg, float** second_arg, int x1, int y1, int x2, int y2)
		{
			assert(x1 == x2);
			assert(y1 == y2); 
			int i, j;
			float** result = create_matrix(x1, y1);

			for (i = 0; i < x1; i++)
			{
				for (j = 0; j < y1; j++)
					result[i][j] = first_arg[i][j] + second_arg[i][j];
			}

			return result;
		}

		float** subtract(float** first_arg, float** second_arg, int x1, int y1, int x2, int y2)
		{
			assert(x1 == x2);
			assert(y1 == y2);
			int i, j;
			float** result = create_matrix(x1, y1);

			for (i = 0; i < x1; i++)
			{
				for (j = 0; j < y1; j++)
					result[i][j] = first_arg[i][j] - second_arg[i][j];
			}

			return result;
		}


		float** transpose(float** arg, int row, int col)
		{
			int i, j;
			float** transposed = create_matrix(col, row);

			for (i = 0; i < row; i++)
			{
				for (j = 0; j < col; j++)
					transposed[j][i] = arg[i][j];
			}
			
			return transposed;
		}

		float** multiply(float** first_arg, float** second_arg, int x1, int y1, int x2, int y2)
		{
			int i, j, k;
			assert(y1 == x2); //making sure multiplication is possible
			
			float** result = create_matrix(x1, y2);

			//initially setting to 0
			for (i = 0; i < x1; i++)
			{
				for (j = 0; j < y2; j++)
					result[i][j] = 0;
			}


			for (k = 0; k < x1; k++) //rowfirst
			{
				for (i = 0; i < y2; i++) //columnsecond
				{
					for (j = 0; j < y1; j++) //colfirst
						result[k][i] += first_arg[k][j] * second_arg[j][i];
				}
			}
			return result;
		 }

	private:
		std::vector<Measurement> m;
		std::vector<Truth> t;
		std::vector<Covariance> c;
		std::vector<State_upd> s;

};

#endif
