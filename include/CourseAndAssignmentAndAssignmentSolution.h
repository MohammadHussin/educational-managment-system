#ifndef COURSEANDASSIGNMENTANDASSIGNMENTSOLUTION_H
#define COURSEANDASSIGNMENTANDASSIGNMENTSOLUTION_H
#include<bits/stdc++.h>
using namespace std;

struct Course
{
    string doctorname;
    string name;
    string abouWhat;
    int id;
    string info();
};
struct Assignment
{
    string doctorName;
    int maxGrade;
    int idOfCourse;
    int idOfAssignment;
    string question;
    int numberOfStudent;
    string info();
};
struct AssignmentSolution
{
    string doctorName;
    string ans;
    string comment;
    int grade=-1;
    int studentID;
    int idOfAssignment;
    int idOfCourse;
    string nameOfStudent;
    string info();
};

#endif // COURSEANDASSIGNMENTANDASSIGNMENTSOLUTION_H
