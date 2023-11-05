#ifndef DOCTOR_H
#define DOCTOR_H
#include<bits/stdc++.h>
using namespace std;

struct Doctor
{
    string name;
    string numberPhone;
    string email;
    string password;
    string userName;
    string type="doctor";
    int id;
    string info();
};

#endif // DOCTOR_H
