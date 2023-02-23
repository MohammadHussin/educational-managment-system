#include "Doctor.h"


string Doctor::info()
{
    string temp;
    temp+=userName;
    temp+=' ';
    temp+=password;
    temp+=' ';
    temp+=type;
    temp+=' ';
    temp+=numberPhone;
    temp+=' ';
    temp+=email;
    temp+=' ';
    temp+=name;
    temp+=' ';
    temp+=to_string(id);
    return temp;
}
