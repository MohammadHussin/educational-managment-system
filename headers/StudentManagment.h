#ifndef STUDENTMANAGMENT_H
#define STUDENTMANAGMENT_H
#include<bits/stdc++.h>
#include"Admin.h"
#include"CourseAndAssignmentAndAssignmentSolution.h"
#include"Doctor.h"
#include"fileFunctions.h"
#include"helperFunctions.h"
#include"Student.h"

struct StudentManagment
{
    Student currentStudent;
    vector<Student>currentStudents;
    vector<Course>registeredCourses;
    vector<Course>unRegisteredCourses;
    vector<Assignment>currentAssignments;
    vector<AssignmentSolution>currentAssignmentsolutions;
    int lastIdPost=0;
    void logIn();
    void signUp();
    void menuOfStudent();
    void sendMessage();
    void gradesReport();
    void registerOnCourse();
    bool listMyCourses();
    void viewCourse(int courseId);
    void createPost(int courseId);
    vector<string> listPost(int courseId);
    void viewPost(string post);
    void listComment(int postId,vector<string>&comments);
    void logOutFromThisCourse(int courseId);
    void setAnswer(int assignmentId,int courseId,string doctorName);
    int listAssignemnt(int courseId);
    void reloadCourses();
    void reloadStudents();
    void reloadAssignment();
    void reloadAssignmentSolution();
    void updateCourses();
    void updateRegisteredCoursesFile(int courseId);
    void updataAssignmentSolution(int courseId);
    void updatePostId();
};
#endif // STUDENTMANAGMENT_H
