#include "Teacher.h"

string Teacher::info()
{
    string temp;
    temp+=userName;
    temp+=' ';
    temp+=password;
    temp+=' ';
    temp+=type;
    temp+=' ';
    temp+=name;
    temp+=' ';
    temp+=email;
    temp+=' ';
    temp+=to_string(use);
    temp+=' ';
    temp+=to_string(id);
    return temp;
}
