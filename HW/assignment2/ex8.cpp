/* ECE373
 * Filename: ex8.cpp
 *
 * Problem: Create the following table.
--------------------------------------------------------------------------------
| Justified Left & w of 39          |         Justified Right & w of 39 |
--------------------------------------------------------------------------------
|                    3.14 |                   3.1416 |                 3.141593 |
--------------------------------------------------------------------------------
|                  645197 |                  2354115 |                    9d84d |
--------------------------------------------------------------------------------
 */
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	double PI = 3.141592653589793;
	int val = 645197;

	/* draw a line across the screen */
//	cout<<setw(39+39)<<setfill('-')<<endl;
        cout<<"--------------------------------------------------------------------------------"<<endl;
	cout<<"|";
	/* insert w of 39 & justify left */
	cout <<setw(39)<<left<< " Justified Left & width of 39 " << "|";

    /* insert w of 39 & justify right */
	cout <<setw(39)<<right<< " Justified Right & width of 39 " << "|" << endl;
	
    /* draw a line across the screen */
        cout<<"--------------------------------------------------------------------------------"<<endl;
	cout<<"|";
	/* insert w of 24 & set precision 3*/
	cout <<setw(24)<<setprecision(3)<<right<< PI <<" |";
 
	/* insert w of 25 & set precision 5*/
    cout <<setw(25)<<setprecision(5)<<right<< PI <<" |";

    /* insert w of 25 & set precision 7*/
    cout <<setw(25)<<setprecision(7)<<right<< PI <<" |"<<endl;

    /* draw a line across the screen */
        cout<<"--------------------------------------------------------------------------------"<<endl;

    cout<<"|";
    /* insert w of 24 & print in base 10*/
    cout <<setw(24)<<setbase(10)<<right<< val <<" |";

    /* insert w of 25 & print in base 8*/
    cout <<setw(25)<<setbase(8)<<right<< val <<" |";

    /* insert w of 25 & print in base 16*/
    cout <<setw(25)<<setbase(16)<<right<< val <<" |"<<endl;


    /* draw a line across the screen */
        cout<<"--------------------------------------------------------------------------------"<<endl;


}

