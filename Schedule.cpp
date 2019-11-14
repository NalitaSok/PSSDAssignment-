#include "Declarations.h"
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{

	//vectors for lecturers courses and rooms
	vector<Lecturers> lectVect;
	vector<Classes> classVect;
	int rooms;

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
	//create optimal timetable

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

					bool placed = false;


					//check every timetable slot for a 1st preference
					for (int l = 0; l < 40; l++)
					{
						int checkPref = initialiseLects[j]->preferences[l];

						if ( l > 2 && (initialiseCourses[i]->finalTimeTable[l - 2] != j || initialiseCourses[i]->finalTimeTable[l - 1] != j))
						{
							
							//check that the course needs more hours
							if ((l !=3 && l != 11 && l != 19 && l != 27 && l != 35) && checkPref == 1 && initialiseCourses[i]->num_hours > 0 && initialiseCourses[i]->finalTimeTable[l] == -1)
							{
									//check if the period runs over the lunch break
									if(! ((l == 4 || l == 12 || l == 20|| l == 28 || l == 36) && initialiseCourses[i]->finalTimeTable[l - 2]  == j)){

										//check if lecturer has been teaching in the past 2 hours, or will be teaching in the next 2 hours
										bool past2hr = false;
										bool past1hr = false;
										bool next1hr = false;
										bool next2hr = false;
										for(int m = 0; m < coursesLength; m++){

											if( l >= 2 && initialiseCourses[m]->finalTimeTable[l - 2] == j)
											{
												past2hr = true;
											}

											if( l >= 1 && initialiseCourses[m]->finalTimeTable[l - 1] == j)
											{
												past1hr = true;
											}

											if(initialiseCourses[m]->finalTimeTable[l + 1] == j)
											{
												next1hr = true;
											}

											if(initialiseCourses[m]->finalTimeTable[l + 2] == j)
											{
												next2hr = true;
											}

										}

										bool limit = false;

										if((past2hr && past1hr) || (next2hr && next1hr)){
											limit = true;
										}

										bool lectisfree = true;
										int coursesScheduled = 0;

										for(int m = 0; m < coursesLength; m++){

											//count how many courses have been scheduled in this period already
											if(initialiseCourses[m]->finalTimeTable[l] != -1){
												coursesScheduled++;
											}

											if(initialiseCourses[m]->finalTimeTable[l] == j)
											{
												lectisfree = false;
											}

										}

										if(lectisfree && coursesScheduled < rooms && !limit){
											if(!placed || (placed && initialiseCourses[i]->finalTimeTable[l-1] != -1) || (placed && initialiseCourses[i]->finalTimeTable[l+1] != -1)){
												initialiseCourses[i]->finalTimeTable[l] = j;

												placed = true;

												//decrease course hours when they are assigned to a lecturer
												initialiseLects[j]->courses[k]->num_hours = initialiseLects[j]->courses[k]->num_hours - 1;
											}
										}
										
									}
								
							}
						}
					}

					//check every timetable slot for a 2nd preference
					for (int l = 0; l < 40; l++)
					{
						int checkPref = initialiseLects[j]->preferences[l];

						if (l > 2 && (initialiseCourses[i]->finalTimeTable[l - 2] != j || initialiseCourses[i]->finalTimeTable[l - 1] != j))
						{

							//check that the course needs more hours and that this slot is empty
							if ((l !=3 && l != 11 && l != 19 && l != 27 && l != 35) && checkPref == 2 && initialiseCourses[i]->num_hours > 0 && initialiseCourses[i]->finalTimeTable[l] == -1)
							{
								

									//check if the period runs over the lunch break
									if(! ((l == 4 || l == 12 || l == 20|| l == 28 || l == 36) && initialiseCourses[i]->finalTimeTable[l - 2]  == j)){

										//check if lecturer has been teaching in the past 2 hours, or will be teaching in the next 2 hours
										bool past2hr = false;
										bool past1hr = false;
										bool next1hr = false;
										bool next2hr = false;
										for(int m = 0; m < coursesLength; m++){

											if( l >= 2 && initialiseCourses[m]->finalTimeTable[l - 2] == j)
											{
												past2hr = true;
											}

											if( l >= 1 && initialiseCourses[m]->finalTimeTable[l - 1] == j)
											{
												past1hr = true;
											}

											if(initialiseCourses[m]->finalTimeTable[l + 1] == j)
											{
												next1hr = true;
											}

											if(initialiseCourses[m]->finalTimeTable[l + 2] == j)
											{
												next2hr = true;
											}

										}

										bool limit = false;

										if((past2hr && past1hr) || (next2hr && next1hr)){
											limit = true;
										}

										bool lectisfree = true;

										int coursesScheduled = 0;

										for(int m = 0; m < coursesLength; m++){

											//count how many courses have been scheduled in this period already
											if(initialiseCourses[m]->finalTimeTable[l] != -1){
												coursesScheduled++;
											}

											if(initialiseCourses[m]->finalTimeTable[l] == j)
											{
												lectisfree = false;
											}

										}

										if(lectisfree && coursesScheduled < rooms && !limit){

											if(!placed || (placed && initialiseCourses[i]->finalTimeTable[l-1] != -1) || (placed && initialiseCourses[i]->finalTimeTable[l+1] != -1)){
												initialiseCourses[i]->finalTimeTable[l] = j;

												placed = true;

												//decrease course hours when they are assigned to a lecturer
												initialiseLects[j]->courses[k]->num_hours = initialiseLects[j]->courses[k]->num_hours - 1;
											}
											
										}
									}
								
							}
						}
					}

					//check every timetable slot for a last preference
					for (int l = 0; l < 40; l++)
					{
						int checkPref = initialiseLects[j]->preferences[l];

						if (l > 2 && (initialiseCourses[i]->finalTimeTable[l - 2] != j || initialiseCourses[i]->finalTimeTable[l - 1] != j))
						{

							//check that the course needs more hours
							if ((l !=3 && l != 11 && l != 19 && l != 27 && l != 35) && checkPref == 5 && initialiseCourses[i]->num_hours > 0 && initialiseCourses[i]->finalTimeTable[l] == -1)
							{
								

									//check if the period runs over the lunch break
									if(! ((l == 4 || l == 12 || l == 20|| l == 28 || l == 36) && initialiseCourses[i]->finalTimeTable[l - 2]  == j)){

										//check if lecturer has been teaching in the past 2 hours, or will be teaching in the next 2 hours
										bool past2hr = false;
										bool past1hr = false;
										bool next1hr = false;
										bool next2hr = false;
										for(int m = 0; m < coursesLength; m++){

											if( l >= 2 && initialiseCourses[m]->finalTimeTable[l - 2] == j)
											{
												past2hr = true;
											}

											if( l >= 1 && initialiseCourses[m]->finalTimeTable[l - 1] == j)
											{
												past1hr = true;
											}

											if(initialiseCourses[m]->finalTimeTable[l + 1] == j)
											{
												next1hr = true;
											}

											if(initialiseCourses[m]->finalTimeTable[l + 2] == j)
											{
												next2hr = true;
											}

										}

										bool limit = false;

										if((past2hr && past1hr) || (next2hr && next1hr)){
											limit = true;
										}


										bool lectisfree = true;

										int coursesScheduled = 0;

										for(int m = 0; m < coursesLength; m++){

											//count how many courses have been scheduled in this period already
											if(initialiseCourses[m]->finalTimeTable[l] != -1){
												coursesScheduled++;
											}

											if(initialiseCourses[m]->finalTimeTable[l] == j)
											{
												lectisfree = false;
											}

										}

										if(lectisfree && coursesScheduled < rooms && !limit){
											if(!placed || (placed && initialiseCourses[i]->finalTimeTable[l-1] != -1) || (placed && initialiseCourses[i]->finalTimeTable[l+1] != -1)){
												initialiseCourses[i]->finalTimeTable[l] = j;

												placed = true;

												//decrease course hours when they are assigned to a lecturer
												initialiseLects[j]->courses[k]->num_hours = initialiseLects[j]->courses[k]->num_hours - 1;
											}
										}
									}
								
							}
						}
					}
				}
			}
		}
	}

	//need to add:
	//check for multiple sessions in a day
	//check if lecturer is teaching too many classes without a break aross courses


	//export result timetable into
	string result2 = "";
	for (int i = 0; i < coursesLength; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			result2 = result2 + to_string(initialiseCourses[i]->finalTimeTable[j]) + ",";
		}
		result2 = result2 + '\n';
	}

	std::ofstream outfile("fnl_soln.sch");

	outfile << result2 << std::endl;

	outfile.close();

	return 0;
}