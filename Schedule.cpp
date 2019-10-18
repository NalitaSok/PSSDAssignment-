#include "Declarations.h"
#include <fstream> 
#include <string> 
#include <sstream> 


using namespace std; 

int main(int argc, char *argv[]){


	//vectors for lecturers courses and rooms 
	vector<Lecturers> lectVect; 
	vector<Classes> classVect;
	int rooms;   

	//TODO
	//read input from file into lecturers & classes
	string fileName(argv[1]); 
    ifstream file(fileName.c_str());
    string line;  
    int i=0; 

	//get number of rooms
	string temp; 
	getline(file,temp); 
	istringstream iss(temp); 
	iss>>temp; 
	iss>>temp; 

	rooms = stoi(temp); 

	//get number of classes
	getline(file,temp); 
	istringstream iss2(temp); 
	iss2>>temp; 
	iss2>>temp; 

	Classes *initialiseCourses[stoi(temp)];
	int coursesLength = stoi(temp); 

	//intialise new classes in array
	for(int i = 0; i < coursesLength; i++){
		initialiseCourses[i] = new Classes;
	}

	getline(file,temp); 
	istringstream iss3(temp); 
	iss3>>temp; 

	// read course contact hours into the array of courses
	for(int i=0;i<coursesLength;i++)
	{
		iss3>>temp; 
		initialiseCourses[i]->num_hours = stoi(temp);
	}

	getline(file,temp); 
	istringstream iss4(temp); 
	iss4>>temp; 

	//read in course names 
	for(int i=0;i<coursesLength;i++)
	{
		iss4>>temp; 
		if(temp[temp.size()-1]==',')
		{
			temp = temp.substr(0,temp.size()-1); 
		}
		//cout<<temp<<endl; 
		initialiseCourses[i]->name = temp;
	}

	//get number of lecturers
	getline(file,temp); 
	istringstream iss5(temp); 
	iss5>>temp; 
	iss5>>temp; 

	Lecturers *initialiseLects[stoi(temp)];
	int lectLength = stoi(temp); 

	//intialise new Lecturers in array
	for(int i = 0; i < lectLength; i++){
		initialiseLects[i] = new Lecturers;
	}

	getline(file,temp); 
	istringstream iss6(temp); 

	//read in lecturer names 
	for(int i=0;i<lectLength;i++)
	{
		iss6>>temp; 
		if(temp[temp.size()-1]==',')
		{
			temp = temp.substr(0,temp.size()-1); 
		}
		initialiseLects[i]->name = temp;
	}

	




	//print rest of file
	while(getline(file,line))
	{
		cout<<line<<endl; 

	}
	//create optimal timetable - algorithm?

	//output result to fnl_soln.sch

	std::string tempresult = "my text here! \nand a new line"; //for testing purposes only
	std::ofstream outfile ("fnl_soln.sch");

	outfile <<  tempresult << std::endl;

	outfile.close();

	return 0;
}