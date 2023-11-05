#include "helperFunctions.h"

string stringWithComma(string &s)
{
    for(int i=0;i<s.size();i++)
    {
        if(s[i]==' ')
        s[i]=',';
    }
    return s;
}
string stringWithoutComma(string s)
{
    for(int i=0;i<s.size();i++)
    {
        if(s[i]==',')
        s[i]=' ';
    }
    return s;
}
bool check(string name,string password,string type)
{

    ifstream f("admin_file.txt");
    if(f.fail())
    {
        cout<<"ERROR can't open this file"<<endl;
        return false;
    }
    string info;
    while(getline(f,info))
    {
        string tempname;
        string tempassword;
        string temptype;
        istringstream iss(info);
        iss>>tempname>>tempassword>>temptype;
        if(tempname==name && tempassword==password && temptype==type)
        {
            f.close();
            return true;
        }
    }
    f.close();
    return false;
}
void allUsers(string path,vector<pair<string,int>>&temp,int currid)
{
    vector<string>v;
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream is(v[i]);
        string name;
        is>>name;
        reverse(v[i].begin(),v[i].end());
        istringstream iss(v[i]);
        int id;
        iss>>id;
        if(id!=currid)
        temp.push_back({name,id});
    }
}

