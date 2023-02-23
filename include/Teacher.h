#ifndef TEACHER_H
#define TEACHER_H
#include <bits/stdc++.h>
using namespace std;

struct Teacher
{
    string userName;
    string name;
    string password;
    string email;
    string type="teacher";
    int use=-1;
    int id;
    string info();
};
#endif // TEACHER_H
