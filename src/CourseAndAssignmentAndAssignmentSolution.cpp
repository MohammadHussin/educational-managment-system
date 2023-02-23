#include "CourseAndAssignmentAndAssignmentSolution.h"

string Course::info()
{
    string temp;
    temp+=doctorname;
    temp+=' ';
    temp+=name;
    temp+=' ';
    temp+=abouWhat;
    temp+=' ';
    temp+=to_string(id);
    return temp;
}
string Assignment::info()
{
    string temp;
    temp+=doctorName;
    temp+=' ';
    temp+=question;
    temp+=' ';
    temp+=to_string(maxGrade);
    temp+=' ';
    temp+=to_string(idOfCourse);
    temp+=' ';
    temp+=to_string(idOfAssignment);
    temp+=' ';
    temp+=to_string(numberOfStudent);
    return temp;
}
string AssignmentSolution::info()
{
    string temp;
    temp+=doctorName;
    temp+=' ';
    temp+=ans;
    temp+=' ';
    temp+=comment;
    temp+=' ';
    temp+=to_string(grade);
    temp+=' ';
    temp+=to_string(studentID);
    temp+=' ';
    temp+=to_string(idOfAssignment);
    temp+=' ';
    temp+=to_string(idOfCourse);
    temp+=' ';
    temp+=nameOfStudent;
    return temp;
}
