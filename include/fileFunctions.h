#ifndef FILEFUNCTIONS_H
#define FILEFUNCTIONS_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;
void writeOnFile(string name,vector<string>&v);
void readFromFile(string name,vector<string>&v);
void addToFile(string name,string info);

#endif // FILEFUNCTIONS_H
