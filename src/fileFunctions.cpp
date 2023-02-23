#include "fileFunctions.h"

void writeOnFile(string name,vector<string>&v)
{
    ofstream f(name.c_str());
    if(f.fail())
    {
        cout<<"ERROR can't open this file"<<endl;
        return;
    }
    for(int i=0;i<v.size();i++)
    f<<v[i]<<endl;
    f.close();
}
void readFromFile(string name,vector<string>&v)
{
    ifstream f(name.c_str());
    if(f.fail())
    {
        cout<<"ERROR can't open this file"<<endl;
        return;
    }
    string info;
    while(getline(f,info))
    v.push_back(info);
    f.close();
}
void addToFile(string name,string info)
{
    ofstream f(name.c_str(),ios::app | ios::out);
    if(f.fail())
    {
        cout<<"ERROR can't open this file"<<endl;
        return;
    }
    f<<info<<endl;
    f.close();
}
