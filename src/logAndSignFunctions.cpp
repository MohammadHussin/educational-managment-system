#include "logAndSignFunctions.h"
int menuOfLogOrSign()
{
    cout<<"1_log in"<<endl;
    cout<<"2_sign up"<<endl;
    cout<<"3_log out"<<endl;
    cout<<"please enter your choice : "<<endl;;
    bool ok=true;
    int choice;
    while(ok)
    {
        cin>>choice;
        if(choice>=1 && choice<=3)
        ok=false;
        if(ok)
        cout<<"Invalid number,please try again"<<endl;
    }
    return choice;
}
int menuOfLog()
{
    cout<<"1_log in as a doctor"<<endl;
    cout<<"2_log in as a student"<<endl;
    cout<<"3_log in as a teacher"<<endl;
    cout<<"4_log in as a admin"<<endl;
    cout<<"please enter your choice : "<<endl;
    bool ok=true;
    int choice;
    while(ok)
    {
        cin>>choice;
        if(choice>=1 && choice<=4)
        ok=false;
        if(ok)
        cout<<"Invalid number,please try again"<<endl;
    }
    return choice;
}
int menuOfSign()
{
    cout<<"1_sign up as a doctor"<<endl;
    cout<<"2_sign up as a student"<<endl;
    cout<<"3_sign up as a teacher"<<endl;
    cout<<"please enter your choice : "<<endl;
    bool ok=true;
    int choice;
    while(ok)
    {
        cin>>choice;
        if(choice>=1 && choice<=3)
        ok=false;
        if(ok)
        cout<<"Invalid number,please try again"<<endl;
    }
    return choice;
}
