#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<utility>
#include<algorithm>
#include "fileFunctions.h"
using namespace std;
string stringWithComma(string &s);
string stringWithoutComma(string s);
bool check(string name,string password,string type);
void allUsers(string path,vector<pair<string,int>>&temp,int currid=0);

#endif // HELPERFUNCTIONS_H
