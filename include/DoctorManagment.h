#ifndef DOCTORMANAGMENT_H
#define DOCTORMANAGMENT_H
#include<bits/stdc++.h>
#include "Admin.h"
#include "CourseAndAssignmentAndAssignmentSolution.h"
#include "Doctor.h"
#include "Teacher.h"
#include "fileFunctions.h"
#include "helperFunctions.h"
using namespace std;

struct DoctorManagment
{
    Doctor currentDoctor;
    vector<Doctor>currentDoctors;
    vector<Course>currentCourses;
    vector<Assignment>currentAssignments;
    vector<AssignmentSolution>currentAssignmentSolutions;
    vector<Teacher>currentTeacher;
    int lastIdCourse=0;
    int lastIdAssignment=0;
    int lastIdPost=0;
    void logIn();
    void signUp();
    void menuOfDoctor();
    void inviteTeacher();
    void realodMessages(vector<string> &currentMessages,string user,int userId,int &lastnum);
    bool listCourses();
    void createCourse();
    void viewCourse(int idOfCourse);
    void createPost(int courseId);
    vector<string> listPost(int courseId);
    void viewPost(string post);
    void listComment(int postId,vector<string>&comments);
    int listAssignment(int idOfCourse);
    void createAssignment(int idOfCourse);
    void deleteAssignment(int idOfAssignment);
    void viewAssignment(int idOfAssignment);
    void showGrades(int idOfAssignmnet);
    bool listSolutions(int idOfAssignmnet);
    void sendMessage();
    void viewSolutionOfStudent(int idOfAssignment);
    void setGrade(int posOfStudent,vector<AssignmentSolution>&curr,bool ok=true);
    void setComment(int posOfStudent,vector<AssignmentSolution>&curr,bool ok=true);
    void deleteCourse(int numberOfCourse);
    void updatePosts(int courseId);
    void reloadDoctors();
    void reloadCourses();
    void reloadAssignments();
    void reloadAssignmentsolutions();
    void reloadTeachers();
    void updateFiles(string path);
    void updateAssignmentsolutin(string path,vector<AssignmentSolution>&curr);
    void updatePostId();
    void updateRegistered(int courseId);
};
#endif // DOCTORMANAGMENT_H
