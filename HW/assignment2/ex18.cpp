/* ECE373
 * Programming C++
 * Filename: ex18.cpp
 *
 * Problem: This exercise shows the functionality of the preprocessor for the
 * compiler, add only the definitions and see how it affects the code and gets it
 * running. Read through the code to see how your definitions change the 
 * rest of the code through the shown preprocessor commands.
 */

/*######################################################*/
/* ONLY ADD YOUR MODIFICATIONS HERE */

/* You will need to define CREATEMAIN and ADDLIBRARIES */
/* CREATEMAIN will throw an error if you do not add a number */
 #define CREATEMAIN 50
 #define ADDLIBRARIES

/* Define the TABLE_SIZE here with #define as 10*/
 #define TABLE_SIZE 10
int table1[TABLE_SIZE];

/* Undefine the TABLE_SIZE with #undef*/
 #undef TABLE_SIZE

/* Define the TABLE_SIZE here with #define as 5*/
 #define TABLE_SIZE 5
int table2[TABLE_SIZE];

/*######################################################*/
/* DO NOT EDIT THE CODE BELOW THIS POINT */

/* This is a macro.
 * It can be used to replace a function call with replacement code
 * you have defined in the macro. The macro arguments (a) and (b) are in 
 * brackets. If the below macro is called with:
 * 		print(variableA,variableB)
 * It then generates the following code:
 * 		cout << "A is:" << variableA << ", B is:" << variableB << endl
 */
#define print(a,b)	(cout << "A is:" << (a) << ", B is:" << (b) << endl)

#ifdef ADDLIBRARIES
/*You will need to define the ADDLIBRARIES to get iostream declared*/
	#include <iostream> 
#endif

using namespace std;

#ifndef CREATEMAIN
	#error Please define CREATEMAIN for the preprocessor as 0.
#elif CREATEMAIN < 50
	#error Please define CREATEMAIN as 50.
#elif CREATEMAIN > 50
	#error Please define CREATEMAIN as 50.
#else
int main()
{
  int ii;
  cout << "This loop will crash the program ";
  cout << "if you did not set the TABLE_SIZE correctly." << endl;
  for (ii=0;ii<TABLE_SIZE;ii++) {
	table1[ii*2]=0;
	table2[ii]=0;
  }
  cout << "Loop is successful." << endl;

  int x=5, y=8;
  print(x,y);

  return 0;
}
#endif
