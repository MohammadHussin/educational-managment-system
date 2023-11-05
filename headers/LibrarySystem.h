#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H
#include<bits/stdc++.h>
#include"TeacherManagment.h"
#include"logAndSignFunctions.h"
#include"StudentManagment.h"
using namespace std;

struct librarySystem
{
    DoctorManagment newDoctor;
    StudentManagment newStudent;
    TeacherManagment newTeacher;
    Admin newAdmin;
    void reload();
    void run();
};
#endif // LIBRARYSYSTEM_H
