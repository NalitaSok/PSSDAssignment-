#include <iostream> 
#include <string>
#include <vector>  

//forward declare to avoid recursion
class Classes;

class Lecturers
{
    public:
    std::string name; //name of the lecturer - for printing purposes
    int course; 
    int lecturers; 

    int preferences[40]; //the preferences of the lecturer for teaching time - each int represents one hour
    std::vector<Classes> courses; //the list of courses this lecturer teaches
    

}; 

class Classes
{
    public:

    std::string name; //name of the course to use when printing
    int num_hours; //number of contact hours that need to be scheduled
    std::vector<Lecturers> teachers; //list of lecturers who will teach the course

    int room; 
    int course; 

}; 