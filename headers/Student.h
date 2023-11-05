#ifndef STUDENT_H
#define STUDENT_H
#include<bits/stdc++.h>
using namespace std;

struct Student
{
    int id;
    string userName;
    string name;
    string password;
    string email;
    string type="student";
    string info();
};

#endif // STUDENT_H
