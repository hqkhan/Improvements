/* ECE373
 * Filename: ex2.cpp
 *
 * Problem: Read an argument from the command line, add it with a number the 
 * user inputs then print out the result.
 */
#include <iostream> 
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc <= 1) {
		cout << "Include a numerical argument when running this program." \
			<< endl;
    } else{
		/* insert your own code here */
		int num=0;
		cin>>num;
		int num2 = atoi(argv[1]);
		num = num2+num;			
		cout<<num<<endl;
		// if there are problems remember to check whether you have endl
	}
}

