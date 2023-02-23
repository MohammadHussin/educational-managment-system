#include "Admin.h"

void Admin::logIn()
{
    string tempName;
    string tempPassword;
    bool ok=true;
    while(ok)
    {
        cout<<"enter your name and password"<<endl;
        cin>>tempName>>tempPassword;
        if(tempName==name && tempPassword==password)
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    menuOfAdmin();
}
void Admin::menuOfAdmin()
{
    vector<string>v;
    readFromFile("admin_file.txt",v);
    cout<<"1_view the registration requests"<<endl;
    cout<<"2_respond to the registration requests"<<endl;
    cout<<"3_log out"<<endl;
    bool ok=true;
    int choice;
    while(ok)
    {
        cout<<"enter your choice"<<endl;
        cin>>choice;
        if(choice>=1 && choice<=3)
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    ok=true;
    if(choice==1)
    {
        for(int i=0;i<v.size();i++)
        {
            istringstream iss(v[i]);
            string name;
            string password;
            string type;
            iss>>name>>password>>type;
            cout<<i+1<<"_the name of the user:"<<stringWithoutComma(name)<<endl
            <<"  the password of the user:"<<password<<endl;
        }
        if(!v.size())
        cout<<"there are no registration requests :("<<endl;
    }
    else if(choice==2)
    {
        int num;
        int choice;
        bool ok=true;
        while(ok)
        {
            cout<<"enter the number of user"<<endl;
            cin>>num;
            if(num>=1 && num<=v.size())
            ok=false;
            if(ok)
            cout<<"invalid input please try again"<<endl;
        }
        cout<<"1_accept"<<endl;
        cout<<"2_reject"<<endl;
        cout<<"3_back"<<endl;
        cin>>choice;
        while(ok)
        {
            cout<<"enter your choice"<<endl;
            cin>>choice;
            if(choice>=1 && choice<=3)
            ok=false;
            if(ok)
            cout<<"invalid input please try again"<<endl;
        }
        if(choice==1)
        {
            istringstream iss(v[num-1]);
            string type;
            iss>>type>>type>>type;
            string nameOfFile=type+"_file.txt";
            addToFile(nameOfFile,v[num-1]);
            v.erase(v.begin()+num-1);
        }
        else if(choice==2)
        v.erase(v.begin()+num-1);
        else
        menuOfAdmin();
    }
    else
    ok=false;
    updateAdmin(v);
    if(ok)
    menuOfAdmin();
}
void Admin::updateAdmin(vector<string>v)
{
    writeOnFile("admin_file.txt",v);
    v.clear();
}
