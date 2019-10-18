#include "Declarations.h"
#include <fstream> 


int main(){

	//TODO
	//read input from file into lecturers & classes

	//create optimal timetable - algorithm?

	//output result to fnl_soln.sch

	std::string tempresult = "my text here! \nand a new line"; //for testing purposes only
	std::ofstream outfile ("fnl_soln.sch");

	outfile <<  tempresult << std::endl;

	outfile.close();

	return 0;
}