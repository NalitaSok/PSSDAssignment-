#include "Declarations.h"
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <algorithm>

using namespace std;

//function that pushes into a vector;

int main(int argc, char *argv[])
{

	//vectors for lecturers courses and rooms
	vector<Lecturers> lectVect;
	vector<Classes> classVect;
	int rooms;

	//TODO
	//read input from file into lecturers & classes
	string fileName(argv[1]);
	ifstream file(fileName.c_str());
	string line;
	int i = 0;

	//get number of rooms
	string temp;
	getline(file, temp);
	istringstream iss(temp);
	iss >> temp;
	iss >> temp;

	rooms = stoi(temp);

	//get number of classes
	getline(file, temp);
	istringstream iss2(temp);
	iss2 >> temp;
	iss2 >> temp;

	Classes *initialiseCourses[stoi(temp)];
	int coursesLength = stoi(temp);

	//intialise new classes in array
	for (int i = 0; i < coursesLength; i++)
	{
		initialiseCourses[i] = new Classes;

		for (int j = 0; j < 40; j++)
		{
			initialiseCourses[i]->finalTimeTable[j] = -1;
		}
	}

	getline(file, temp);
	istringstream iss3(temp);
	iss3 >> temp;

	// read course contact hours into the array of courses
	for (int i = 0; i < coursesLength; i++)
	{
		iss3 >> temp;
		initialiseCourses[i]->num_hours = stoi(temp);
	}

	getline(file, temp);
	istringstream iss4(temp);
	iss4 >> temp;

	//read in course names
	for (int i = 0; i < coursesLength; i++)
	{
		iss4 >> temp;
		if (temp[temp.size() - 1] == ',')
		{
			temp = temp.substr(0, temp.size() - 1);
		}
		initialiseCourses[i]->name = temp;
	}

	//get number of lecturers
	getline(file, temp);
	istringstream iss5(temp);
	iss5 >> temp;
	iss5 >> temp;

	Lecturers *initialiseLects[stoi(temp)];
	int lectLength = stoi(temp);

	//intialise new Lecturers in array
	for (int i = 0; i < lectLength; i++)
	{
		initialiseLects[i] = new Lecturers;
	}

	getline(file, temp);
	istringstream iss6(temp);

	//read in lecturer names
	for (int i = 0; i < lectLength; i++)
	{
		iss6 >> temp;
		if (temp[temp.size() - 1] == ',')
		{
			temp = temp.substr(0, temp.size() - 1);
		}
		initialiseLects[i]->name = temp;
	}

	//get rid of descriptor line
	getline(file, temp);

	//The TL section
	istringstream iss7("");
	//read in lecturer and class pairings
	for (int x = 0; x < coursesLength; x++)
	{
		iss7.clear();
		iss7.str("");
		getline(file, temp);
		iss7.str(temp);
		for (int y = 0; y < lectLength; y++)
		{
			getline(iss7, temp, ',');
			if (stoi(temp))
			{
				// lecturer(j).courses.push_back(course(i))
				initialiseLects[y]->courses.push_back(&(*initialiseCourses[x]));
				// course(i).lecturers.push_back(lecturer(j))
				initialiseCourses[x]->teachers.push_back(&(*initialiseLects[y]));
			}
		}
	}

	//get rid of descriptor line
	getline(file, temp);

	//clear iss
	iss7.clear();
	iss7.str("");

	for (int i = 0; i < lectLength; i++)
	{
		iss7.clear();
		iss7.str("");
		getline(file, temp);
		iss7.str(temp);
		for (int j = 0; j < 40; j++)
		{
			getline(iss7, temp, ',');
			initialiseLects[i]->preferences[j] = stoi(temp);
		}
	}

	vector<string> result;
	//create optimal timetable - algorithm?

	//loop through courses
	for (int i = 0; i < coursesLength; i++)
	{
		//get all lecturers who teach this course
		for (int j = 0; j < lectLength; j++)
		{
			//check every lecturer's courses
			for (int k = 0; k < initialiseLects[j]->courses.size(); k++)
			{
				//check for a match
				if (initialiseLects[j]->courses[k]->name == initialiseCourses[i]->name)
				{

					// for (int l = 0; l < 40; l++)
					// {
					// 	preferencesTemp[l] = -1;
					// }
					for (int l = 0; l < 40; l++)
					{
						int checkPref = initialiseLects[j]->preferences[l];

						if (l > 2 && (initialiseCourses[i]->finalTimeTable[l - 2] != j || initialiseCourses[i]->finalTimeTable[l - 1] != j))
						{
							//uncomment the if statement below to always restrict teaching to
							//only 2 hours
							//and check that the course needs more hours
							//TODO add lecturers max hour counter
							if (checkPref == 1 && initialiseCourses[i]->num_hours > 0)
							{

								initialiseCourses[i]->finalTimeTable[l] = j;
								//decrease course hours when they are assigned to a lecturer
								initialiseLects[j]->courses[k]->num_hours = initialiseLects[j]->courses[k]->num_hours - 1; //<< endl;
							}
						}
					}
				}
			}
		}

		// int temp = initialiseLects[i]->courses[0]->num_hours;
		//testing, will put into a vector when this is solved
		// int preferencesTemp[40];
		// string tempStore;

		//set the lecturers if it's 1s

		//storing.push_back(preferencesTemp);
		//cout<<tempStore;
		//result.push_back(tempStore);
	}
	string result2 = "";
	for (int i = 0; i < coursesLength; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			result2 = result2 + to_string(initialiseCourses[i]->finalTimeTable[j]) + ",";
		}
		result2 = result2 + '\n';
	}

	// for (int i = 0; i < result.size(); i++)
	// {
	// 	cout << result.at(i) << endl;
	// }

	//output result to fnl_soln.sch

	std::string tempresult = "my text here! \nand a new line"; //for testing purposes only
	std::ofstream outfile("fnl_soln.sch");

	outfile << result2 << std::endl;

	outfile.close();

	return 0;
}