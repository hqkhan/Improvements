#include <iostream>
#include "Reader.h"
#include <string>


int main(){

	std::ifstream measure("C:/Users/hka0211/Documents/Practice/C++/measurement.csv"); // backslash '\'  is an escape character
	std::ifstream truth("C:/Users/hka0211/Documents/Practice/C++/truth.csv");
	Reader read = Reader(&measure, &truth);  

	//print stuff

	return 0;
}
