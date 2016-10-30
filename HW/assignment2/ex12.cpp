/* ECE373
 * Filename: ex12.cpp
 *
 * Problem: Find the highest values in the multidimensional array1 or array2,
 * for the first level of elements. Then place the results in array3. 
 */
#include <iostream> 

using namespace std;

/* Here are a number of ways to declare arrays */
// multidimensional array
int array1[4][5] = {{124, 20, 67, 25, 35}, {10, 223, 53, 74, 1231}, 
				{14, 23, 573, 43, 767} ,{10250, 10, 20, 32, 23}}; 
// size is automatically created through definition
int array2[] = {2, 4, 10270, 8}; 
// empty array
int array3[4];

int main()
{
	int ii, counter;
	/*Insert code to place the highest first level of elements into array 3*/
	
	for (ii=0;ii<4;ii++) {
		int max = array1[ii][0]; //setting first column and ii row to max
		for (counter=1;counter<5;counter++){
			if(array1[ii][counter] > max) max = array1[ii][counter]; //change max from array1 if found a new max
		}
		
		if (array2[ii] > max) max = array2[ii];
		array3[ii] = max;
		
		cout << array3[ii] << endl;
	}
}

