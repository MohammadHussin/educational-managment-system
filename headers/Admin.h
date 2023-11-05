#ifndef ADMIN_H
#define ADMIN_H
#include<bits/stdc++.h>
#include "helperFunctions.h"
#include "fileFunctions.h"
using namespace std;
struct Admin
{
    string name="mohammad";
    string password="123456789";
    void logIn();
    void menuOfAdmin();
    void updateAdmin(vector<string>v);
};
#endif // ADMIN_H
