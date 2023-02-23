#ifndef TEACHERMANAGMENT_H
#define TEACHERMANAGMENT_H
#include<bits/stdc++.h>
#include "Admin.h"
#include "CourseAndAssignmentAndAssignmentSolution.h"
#include "Doctor.h"
#include "Teacher.h"
#include "fileFunctions.h"
#include "helperFunctions.h"
#include "DoctorManagment.h"
#include "Student.h"
using namespace std;

struct TeacherManagment : DoctorManagment
{
    Teacher currentTeacher;
    vector<Course>currentCourses;
    vector<Assignment>currentAssignments;
    vector<AssignmentSolution>currentAssignmentSolutions;
    vector<Teacher>currentTeachers;
    vector <Doctor> currentDoctors;
    vector<Student>currentStudents;
    int lastId=0;
    int lastIdPost=0;
    void logIn();
    void signUp();
    void menuOfTeacher();
    void sendMessage();
    void viewCourse(int courseId);
    void createPost(int courseId);
    void viewPost(string post);
    void viewAssignment(int courseId,int AssignmentId);
    void viewSolution(int numberOfSolution);
    int listSolutions(int courseId,int assignmentId);
    bool listCourses();
    int listAssignment(int courseId);
    void viewInvitesToMe();
    void reloadTeachers();
    void reloadCourses();
    void reloadAssignment();
    void reloadAssignmentSolution();
    void reloadStudents();
    void reloadDoctors();
    void updateTeachers();
    void updateInviteTeacher(vector<string>v);
};

#endif // TEACHERMANAGMENT_H
