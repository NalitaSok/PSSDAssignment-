#include "Solution.cpp"
#include "EvalUCS.cpp"

int main(){

ProblemUCS* temp1  = new ProblemUCS();

temp1->readUCSInstance("medium1.ucs");
Solution* temp  = new Solution();




temp->readSolution("fnl_soln.sch");

cout << temp->Timetable.size() << endl;

temp->printTimetable(temp->Timetable, temp1->cNames, temp1->lNames);

int failedConstraints = temp->checkConstraints(temp->Timetable, temp1->rooms, temp1->cHours, temp1->LP, temp1->cNames, temp1->lNames);

cout << temp->getFitnessValue(temp->Timetable, temp1->mC, temp1->LP, temp1->cHours, failedConstraints) << endl;

return 0;
}
