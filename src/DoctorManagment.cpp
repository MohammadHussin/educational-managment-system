#include "DoctorManagment.h"

void DoctorManagment::logIn()
{
    bool ok=true;
    while(ok)
    {
        cout<<"enter your username: "<<endl;
        string name;
        string password;
        cin.ignore();
        getline(cin,name);
        stringWithComma(name);
        cout<<"enter your password: "<<endl;
        cin>>password;
        if(check(name,password,"doctor"))
        {
            cout<<"please try again later until you are accepted by the admin"<<endl;
            ok=true;
            break;
        }
        for(int i=0;i<currentDoctors.size();i++)
        {
            if(currentDoctors[i].userName==name && currentDoctors[i].password==password)
            {
                currentDoctor.userName=name;
                currentDoctor.password=password;
                currentDoctor.email=currentDoctors[i].email;
                currentDoctor.name=currentDoctors[i].name;
                currentDoctor.numberPhone=currentDoctors[i].numberPhone;
                currentDoctor.id=currentDoctors[i].id;
                ok=false;
                break;
            }
        }
        if(ok)
        cout<<"Invalid Username or password,please try again"<<endl;
    }
    reloadCourses();
    reloadAssignments();
    reloadAssignmentsolutions();
    menuOfDoctor();
}
void DoctorManagment::signUp()
{
    bool ok=true;
    string name;
    while(ok)
    {
        ok=false;
        cout<<"enter your username: "<<endl;
        cin.ignore();
        getline(cin,name);
        stringWithComma(name);
        for(int i=0;i<currentDoctors.size();i++)
        {
            if(currentDoctors[i].userName==name)
            {
                ok=false;
                break;
            }
        }
        if(ok)
        cout<<"Invalid Username or password,please try again"<<endl;
    }
    currentDoctor.userName=name;
    cout<<"enter your password: "<<endl;
    cin>>currentDoctor.password;
    cout<<"enter your number phone: "<<endl;
    cin>>currentDoctor.numberPhone;
    cout<<"enter your  name: "<<endl;
    cin>>currentDoctor.name;
    cout<<"enter your email: "<<endl;
    cin>>currentDoctor.email;
    currentDoctor.id=currentDoctors.size()+1;
    addToFile("admin_file.txt",currentDoctor.info());
    cout<<"Please wait until you are accepted by the admin"<<endl;
}
void DoctorManagment::menuOfDoctor()
{
    cout<<"1_list courses"<<endl;
    cout<<"2_create course"<<endl;
    cout<<"3_view course"<<endl;
    cout<<"4_delete course"<<endl;
    cout<<"5_invite teacher"<<endl;
    cout<<"6_view messages to me"<<endl;
    cout<<"7_view messages from me"<<endl;
    cout<<"8_sent message"<<endl;
    cout<<"9_back"<<endl;
    cout<<"enter your choice"<<endl;
    bool ok=true;
    int choice;
    while(ok)
    {
        cin>>choice;
        if(choice>=1 && choice<=9)
        ok=false;
        if(ok)
        cout<<"Invalid number,please try again"<<endl;
    }
    ok=true;
    if(choice==1)
    listCourses();
    else if(choice==2)
    createCourse();
    else if(choice==3)
    {
        if(listCourses())
        {
            bool ok=true;
            int num;
            while(ok)
            {
                cout<<"enter the number of the course:"<<endl;
                cin>>num;
                if(num>=1 && num<=currentCourses.size())
                ok=false;
                if(ok)
                cout<<"Invalid number,please try again"<<endl;
            }
            viewCourse(currentCourses[num-1].id);
        }
    }
    else if(choice==4)
    {
        if(listCourses())
        {
            bool ok=true;
            int num;
            while(ok)
            {
                cout<<"enter the number of the course:"<<endl;
                cin>>num;
                if(num>=1 && num<=currentCourses.size())
                ok=false;
                if(ok)
                cout<<"Invalid number,please try again"<<endl;
            }
            deleteCourse(num);
        }
    }
    else if(choice==5)
    {
        reloadTeachers();
        inviteTeacher();
    }
    else if(choice==6)
    {
        vector<string>v;
        string path="messages_file.txt";
        readFromFile(path,v);
        int coun=0;
        for(int i=0;i<v.size();i++)
        {
            istringstream iss(v[i]);
            string message;
            int send;
            int rec;
            string typesend;
            string typerec;
            iss>>message>>send>>rec>>typesend>>typerec;
            if(rec==currentDoctor.id && typerec=="doctor")
            {
                cout<<typesend<<" with id "<<send<<" sent message:"<<stringWithoutComma(message)<<endl;
                coun++;
            }
        }
        if(!coun)
        cout<<"there are no messages to you :("<<endl;
    }
    else if(choice==7)
    {
        vector<string>v;
        string path="messages_file.txt";
        readFromFile(path,v);
        int coun=0;
        for(int i=0;i<v.size();i++)
        {
            istringstream iss(v[i]);
            string message;
            int send;
            int rec;
            string typesend;
            string typerec;
            iss>>message>>send>>rec>>typesend>>typerec;
            if(send==currentDoctor.id && typesend=="doctor")
            {
                cout<<"you send to "<<typerec<<" with id "<<rec<<" and your message :"<<stringWithoutComma(message)<<endl;
                coun++;
            }
        }
        if(!coun)
        cout<<"there are no messages from you :("<<endl;
    }
    else if(choice==8)
    sendMessage();
    else
    ok=false;
    if(ok)
    menuOfDoctor();
}
void DoctorManagment::inviteTeacher()
{
    for(int i=0;i<currentTeacher.size();i++)
    {

        cout<<i+1<<"_ the name of the teacher:"<<currentTeacher[i].userName<<endl
        <<"email:"<<currentTeacher[i].email<<endl;
    }
    if(!currentTeacher.size())
    {
        cout<<"there are no teachers :("<<endl;
        return;
    }
    int choice;
    bool ok=true;
    while(ok)
    {
        cout<<"please enter your choice"<<endl;
        cin>>choice;
        if(choice>=1 && choice<=currentTeacher.size())
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    string temp;
    temp+=to_string(currentDoctor.id);
    temp+=' ';
    temp+=to_string(currentTeacher[choice-1].id);
    addToFile("inviteteacher_file.txt",temp);
}
void DoctorManagment::sendMessage()
{
    cout<<"1_to doctor"<<endl;
    cout<<"2_to student"<<endl;
    cout<<"3_to teacher"<<endl;
    cout<<"4_back"<<endl;
    int choice;
    bool ok=true;
    while(ok)
    {
        cout<<"please enter your choice"<<endl;
        cin>>choice;
        if(choice>=1 && choice<=4)
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    ok=true;
    if(choice==1)
    {
        vector<pair<string,int>>v;
        string path="doctor_file.txt";
        allUsers(path,v,currentDoctor.id);
        if(!v.size())
        {
            cout<<"there are no doctors yet :( "<<endl;
            return;
        }
        for(int i=0;i<v.size();i++)
        cout<<"doctor name:"<<stringWithoutComma(v[i].first)<<endl<<"doctor id:"<<v[i].second<<endl;
        cout<<"enter the id of doctor"<<endl;
        int id;
        cin>>id;
        string message;
        cout<<"enter your message"<<endl;
        cin.ignore();
        getline(cin,message);
        stringWithComma(message);
        string temp;
        temp+=message;
        temp+=' ';
        temp+=to_string(currentDoctor.id);
        temp+=' ';
        temp+=to_string(id);
        temp+=' ';
        temp+="doctor";
        temp+=' ';
        temp+="doctor";
        addToFile("messages_file.txt",temp);
    }
    else if(choice==2)
    {
        vector<pair<string,int>>v;
        string path="student_file.txt";
        allUsers(path,v);
        if(!v.size())
        {
            cout<<"there are no students yet :( "<<endl;
            return;
        }
        for(int i=0;i<v.size();i++)
        cout<<"student name:"<<stringWithoutComma(v[i].first)<<endl<<"student id:"<<v[i].second<<endl;
        cout<<"enter the id of student"<<endl;
        int id;
        cin>>id;
        string message;
        cout<<"enter your message"<<endl;
        cin.ignore();
        getline(cin,message);
        stringWithComma(message);
        string temp;
        temp+=message;
        temp+=' ';
        temp+=to_string(currentDoctor.id);
        temp+=' ';
        temp+=to_string(id);
        temp+=' ';
        temp+="doctor";
        temp+=' ';
        temp+="student";
        addToFile("messages_file.txt",temp);
    }
    else if(choice==3)
    {
        vector<pair<string,int>>v;
        string path="teacher_file.txt";
        allUsers(path,v);
        if(!v.size())
        {
            cout<<"there are no teachers yet :( "<<endl;
            return;
        }
        for(int i=0;i<v.size();i++)
        cout<<"teacher name:"<<stringWithoutComma(v[i].first)<<endl<<"teacher id:"<<v[i].second<<endl;
        cout<<"enter the id of teacher"<<endl;
        int id;
        cin>>id;
        string message;
        cout<<"enter your message"<<endl;
        cin.ignore();
        getline(cin,message);
        stringWithComma(message);
        string temp;
        temp+=message;
        temp+=' ';
        temp+=to_string(currentDoctor.id);
        temp+=' ';
        temp+=to_string(id);
        temp+=' ';
        temp+="doctor";
        temp+=' ';
        temp+="teacher";
        addToFile("messages_file.txt",temp);
    }
    else
    ok=false;
    if(ok)
    sendMessage();
}
void DoctorManagment::realodMessages(vector<string> &currentMessages,string user,int userId,int &lastnum)
{
    vector<string>v;
    string path;
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        string message;
        int id1;
        int id2;
        string type1;
        string type2;
        int num;
        istringstream iss(v[i]);
        iss>>message>>id1>>id2>>type1>>type2>>num;
        if((id1==currentDoctor.id && id2==userId && type1=="doctor" && type2==user) || (id1==userId && id2==currentDoctor.id && type1==user && type2=="doctor"))
        {
            if(num>lastnum)
            {
                currentMessages.push_back(message);
                lastnum=num;
            }
        }
    }
}
bool DoctorManagment::listCourses()
{
    bool ok=false;
    for(int i=0;i<currentCourses.size();i++)
    {
        cout<<i+1<<"_the name of the course: "<<currentCourses[i].name<<endl;
        cout<<"\tnote: "<<currentCourses[i].abouWhat<<endl;
        ok=true;
    }
    if(!ok)
    cout<<"there are no courses yet :)"<<endl;
    return ok;
}
void DoctorManagment::createCourse()
{
    bool ok=true;
    string name;
    Course currentCourse;
    cout<<"enter the name of the course: "<<endl;
    cin.ignore();
    getline(cin,name);
    stringWithComma(name);
    currentCourse.name=name;
    string information;
    cout<<"please enter information about this course: "<<endl;
    cin.ignore();
    getline(cin,information);
    stringWithComma(information);
    currentCourse.abouWhat=information;
    currentCourse.doctorname=currentDoctor.userName;
    currentCourse.id=++lastIdCourse;
    currentCourses.push_back(currentCourse);
    addToFile("course_file.txt",currentCourse.info());
}
void DoctorManagment::viewCourse(int idOfCourse)
{
    cout<<"1_list assignment"<<endl;
    cout<<"2_create assignment"<<endl;
    cout<<"3_view assignment"<<endl;
    cout<<"4_delete assignment"<<endl;
    cout<<"5_create post"<<endl;
    cout<<"6_list post"<<endl;
    cout<<"7_view post"<<endl;
    cout<<"8_back"<<endl;
    cout<<"enter your choice"<<endl;
    bool ok=true;
    int choice;
    while(ok)
    {
        cin>>choice;
        if(choice>=1 && choice<=8)
        ok=false;
        if(ok)
        cout<<"Invalid number,please try again"<<endl;
    }
    ok=true;
    if(choice==1)
    listAssignment(idOfCourse);
    else if(choice==2)
    createAssignment(idOfCourse);
    else if(choice==3)
    {
        int counOfAssignmnet=listAssignment(idOfCourse);
        if(counOfAssignmnet)
        {
            bool ok=true;
            int numberOfAssignment;
            while(ok)
            {
                cout<<"enter the number of the Assignment:"<<endl;
                cin>>numberOfAssignment;
                if(numberOfAssignment>=1 && numberOfAssignment<=counOfAssignmnet)
                ok=false;
                if(ok)
                cout<<"Invalid number,please try again"<<endl;
            }
            int id=0;
            for(int i=0;i<currentAssignments.size();i++)
            {
                if(currentAssignments[i].idOfCourse==idOfCourse)
                {
                    id++;
                    if(id==numberOfAssignment)
                    {
                        numberOfAssignment=i+1;
                        break;
                    }
                }
            }
            viewAssignment(currentAssignments[numberOfAssignment-1].idOfAssignment);
        }
    }
    else if(choice==4)
    {
        int counOfAssignmnet=listAssignment(idOfCourse);
        if(counOfAssignmnet)
        {
            bool ok=true;
            int numberOfAssignment;
            while(ok)
            {
                cout<<"enter the number of the Assignment:"<<endl;
                cin>>numberOfAssignment;
                if(numberOfAssignment>=1 && numberOfAssignment<=counOfAssignmnet)
                ok=false;
                if(ok)
                cout<<"Invalid number,please try again"<<endl;
            }
            int id=0;
            for(int i=0;i<currentAssignments.size();i++)
            {
                if(currentAssignments[i].idOfCourse==idOfCourse)
                {
                    id++;
                    if(id==numberOfAssignment)
                    {
                        numberOfAssignment=i+1;
                        break;
                    }
                }
            }
            deleteAssignment(currentAssignments[numberOfAssignment-1].idOfAssignment);
        }
    }
    else if(choice==5)
    createPost(idOfCourse);
    else if(choice==6)
    listPost(idOfCourse);
    else if(choice==7)
    {
        vector<string>posts=listPost(idOfCourse);
        if(posts.size())
        {
            int choice;
            bool ok=true;
            while(ok)
            {
                cout<<"enter your choice:"<<endl;
                cin>>choice;
                if(choice>=1 && choice<=posts.size())
                ok=false;
                if(ok)
                cout<<"invalid input please try again"<<endl;
            }
            viewPost(posts[choice-1]);
        }
    }
    else
    ok=false;
    if(ok)
    viewCourse(idOfCourse);
}
void DoctorManagment::createPost(int courseId)
{
    updatePostId();
    string contentOfPost;
    cout<<"please enter the content of the post"<<endl;
    cin.ignore();
    getline(cin,contentOfPost);
    stringWithComma(contentOfPost);
    int id=++lastIdPost;
    string temp;
    temp+=contentOfPost;
    temp+=' ';
    temp+=to_string(id);
    temp+=' ';
    temp+=to_string(currentDoctor.id);
    temp+=' ';
    temp+="doctor";
    temp+=' ';
    temp+=to_string(courseId);
    addToFile("posts_file.txt",temp);
}
vector<string> DoctorManagment::listPost(int courseId)
{
    vector<string>v;
    string path="posts_file.txt";
    readFromFile(path,v);
    int coun=0;
    vector<string>temp;
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        string content;
        int postId;
        int userId;
        string user;
        int tempCourseId;
        iss>>content>>postId>>userId>>user>>tempCourseId;
        if(tempCourseId==courseId)
        {
            cout<<coun+1<<"_this post was posted by "<<user<<" with id:"<<userId<<endl;
            temp.push_back(v[i]);
            coun++;
        }
    }
    if(!coun)
    cout<<"there are no posts on this course :("<<endl;
    return temp;
}
void DoctorManagment::viewPost(string post)
{
    istringstream iss(post);
    string content;
    int postId;
    int userId;
    string user;
    int tempCourseId;
    iss>>content>>postId>>userId>>user>>tempCourseId;
    cout<<"1_view the content of this post"<<endl;
    cout<<"2_sent comment"<<endl;
    cout<<"3_back"<<endl;
    int choice;
    bool ok=true;
    while(ok)
    {
        cout<<"please enter your choice"<<endl;
        cin>>choice;
        if(choice>=1 && choice<=3)
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    ok=true;
    if(choice==1)
    {
        int coun=1;
        cout<<"this post was posted by "<<user<<" with id:"<<userId<<endl;
        cout<<"content:"<<stringWithoutComma(content)<<endl;
        cout<<"comments:"<<endl;
        vector<string>v;
        listComment(postId,v);
        for(int i=0;i<v.size();i++)
        {
            istringstream iss(v[i]);
            string content;
            int temppostId;
            int userId;
            string typeUser;
            string typePost;
            iss>>content>>temppostId>>userId>>typeUser>>typePost;
            cout<<'\t'<<i+1<<" the "<<typeUser<<" with the id "<<userId<<':'<<stringWithoutComma(content)<<endl;
        }
        if(!v.size())
        cout<<"there are no comments on this post :("<<endl;

    }
    else if(choice==2)
    {
        cout<<"enter your comment"<<endl;
        cin.ignore();
        string comment;
        getline(cin,comment);
        stringWithComma(comment);
        string path="messages_file.txt";
        string temp;
        temp+=comment;
        temp+=' ';
        temp+=to_string(currentDoctor.id);
        temp+=' ';
        temp+=to_string(postId);
        temp+=' ';
        temp+="doctor";
        temp+=' ';
        temp+="post";
        addToFile(path,temp);
    }
    else
    ok=false;
    if(ok)
    viewPost(post);
}
void DoctorManagment::listComment(int postId,vector<string>&comments)
{
    string path="messages_file.txt";
    vector<string>temp;
    readFromFile(path,temp);
    for(int i=0;i<temp.size();i++)
    {
        istringstream iss(temp[i]);
        string content;
        int temppostId;
        int userId;
        string typeUser;
        string typePost;
        iss>>content>>userId>>temppostId>>typeUser>>typePost;
        if(temppostId==postId && typePost=="post")
        comments.push_back(temp[i]);
    }
}
int DoctorManagment::listAssignment(int idOfCourse)
{
    int coun=0;
    int id=1;
    for(int i=0;i<currentAssignments.size();i++)
    {
        if(currentAssignments[i].idOfCourse==idOfCourse)
        {
            cout<<id<<"_""the question is :"<<stringWithoutComma(currentAssignments[i].question)<<endl
            <<"the max grade is :"<<currentAssignments[i].maxGrade<<endl;
            coun++;
            id++;
        }
    }
    if(!coun)
    cout<<"there are no assignment yet :("<<endl;
    return coun;
}
void DoctorManagment::createAssignment(int idOfCourse)
{
    string question;
    cout<<"enter the questuon please: "<<endl;
    cin.ignore();
    getline(cin,question);
    stringWithComma(question);
    Assignment tempAssignment;
    cout<<"enter the grade of the Assignment: "<<endl;
    int grade;
    cin>>grade;
    tempAssignment.maxGrade=grade;
    tempAssignment.idOfCourse=idOfCourse;
    tempAssignment.question=question;
    tempAssignment.idOfAssignment=++lastIdAssignment;
    tempAssignment.doctorName=currentDoctor.userName;
    tempAssignment.numberOfStudent=0;
    currentAssignments.push_back(tempAssignment);
    addToFile("assignment_file.txt",tempAssignment.info());
}
void DoctorManagment::deleteAssignment(int idOfAssignment)
{
    vector<Assignment>tempAssignments;
    vector<AssignmentSolution>tempAssignmentsolutions;
    for(int i=0;i<currentAssignments.size();i++)
    {
        if(currentAssignments[i].idOfAssignment!=idOfAssignment)
        tempAssignments.push_back(currentAssignments[i]);
    }
    currentAssignments=tempAssignments;
    for(int i=0;i<currentAssignmentSolutions.size();i++)
    {
        if(currentAssignmentSolutions[i].idOfAssignment!=idOfAssignment)
        tempAssignmentsolutions.push_back(currentAssignmentSolutions[i]);
    }
    currentAssignmentSolutions=tempAssignmentsolutions;
    updateFiles("assignment_file.txt");
    updateFiles("assignmentsolution_file.txt");
}
void DoctorManagment::viewAssignment(int idOfAssignment)
{
    reloadAssignmentsolutions();
    cout<<"1_show information"<<endl;
    cout<<"2_show grades"<<endl;
    cout<<"3_list solutions"<<endl;
    cout<<"4_view solution of student"<<endl;
    cout<<"5_back"<<endl;
    int choice;
    bool ok=true;
    while(ok)
    {
        cout<<"enter your choice: "<<endl;
        cin>>choice;
        if(choice>=1 && choice<=5)
        ok=false;
        if(ok)
        cout<<"Invalid number,please try again"<<endl;
    }
    ok=true;
    if(choice==1)
    {
        for(int i=0;i<currentAssignments.size();i++)
        {
            if(currentAssignments[i].idOfAssignment==idOfAssignment)
            {
                cout<<"the question of this assignment is: "<<stringWithComma(currentAssignments[i].question)<<endl;
                cout<<"the number of students that answered on this question is: "<<currentAssignments[i].numberOfStudent<<endl;
                cout<<"the max grade of this assignment is: "<<currentAssignments[i].maxGrade<<endl;
                break;
            }
        }
    }
    else if(choice==2)
    showGrades(idOfAssignment);
    else if(choice==3)
    listSolutions(idOfAssignment);
    else if(choice==4)
    {
        if(listSolutions(idOfAssignment))
        viewSolutionOfStudent(idOfAssignment);
    }
    else
    ok=false;
    if(ok)
    viewAssignment(idOfAssignment);
}
void DoctorManagment::showGrades(int idOfAssignmnet)
{
    bool ok=true;
    for(int i=0;i<currentAssignmentSolutions.size();i++)
    {
        if(currentAssignmentSolutions[i].idOfAssignment==idOfAssignmnet)
        {
            cout<<"studen tid:"<<currentAssignmentSolutions[i].studentID<<"student grade:"<<currentAssignmentSolutions[i].grade<<endl;
            ok=false;
        }
    }
    if(ok)
    cout<<"there are no solutions yet :("<<endl;
}
bool DoctorManagment::listSolutions(int idOfAssignmnet)
{
    bool ok=true;
    for(int i=0;i<currentAssignmentSolutions.size();i++)
    {
        if(currentAssignmentSolutions[i].idOfAssignment==idOfAssignmnet)
        {
            cout<<"student id:"<<currentAssignmentSolutions[i].studentID<<endl
            <<"    student answer:"<<stringWithoutComma(currentAssignmentSolutions[i].ans)<<endl;
            ok=false;
        }
    }
    if(ok)
    cout<<"there are no solutions yet :("<<endl;
    return !ok;
}
void DoctorManagment::viewSolutionOfStudent(int idOfAssignment)
{
    cout<<"enter the id of student:"<<endl;
    int num;
    cin>>num;
    bool ok=true;
    int pos;
    for(int i=0;i<currentAssignmentSolutions.size();i++)
    {
        if(currentAssignmentSolutions[i].studentID==num && currentAssignmentSolutions[i].idOfAssignment==idOfAssignment)
        {
            ok=false;
            pos=i;
            break;
        }
    }
    if(ok)
    {
        cout<<"this student didn't answer yet"<<endl;
        return;
    }
    cout<<"1_set grade"<<endl;
    cout<<"2_set comment"<<endl;
    cout<<"3_set grade and comment"<<endl;
    cout<<"4_bcak"<<endl;
    int choice;
    ok=true;
    while(ok)
    {
        cout<<"please enter your choice"<<endl;
        cin>>choice;
        if(choice>=1 && choice<=4)
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    if(choice==1)
    setGrade(pos,currentAssignmentSolutions);
    else if(choice==2)
    setComment(pos,currentAssignmentSolutions);
    else
    {
        setGrade(pos,currentAssignmentSolutions);
        setComment(pos,currentAssignmentSolutions);
    }
}
void DoctorManagment::setGrade(int posOfStudent,vector<AssignmentSolution>&curr,bool ok)
{
    cout<<"enter the grade"<<endl;
    int num;
    cin>>num;
    curr[posOfStudent].grade=num;
    if(!ok)
    updateAssignmentsolutin("assignmentsolution_file.txt",curr);
    else
    updateFiles("assignmentsolution_file.txt");
}
void DoctorManagment::setComment(int posOfStudent,vector<AssignmentSolution>&curr,bool ok)
{
    cout<<"enter the comment"<<endl;
    string comment;
    cin.ignore();
    getline(cin,comment);
    stringWithComma(comment);
    curr[posOfStudent].comment=comment;
    if(!ok)
    updateAssignmentsolutin("assignmentsolution_file.txt",curr);
    else
    updateFiles("assignmentsolution_file.txt");
}
void DoctorManagment::deleteCourse(int numberOfCourse)
{
    int tempId=currentCourses[numberOfCourse-1].id;
    currentCourses.erase(currentCourses.begin()+numberOfCourse-1);
    vector<Assignment>tempAssignments;
    vector<AssignmentSolution>tempAssignmentsolutions;
    for(int i=0;i<currentAssignments.size();i++)
    {
        if(currentAssignments[i].idOfCourse!=tempId)
        tempAssignments.push_back(currentAssignments[i]);
    }
    currentAssignments=tempAssignments;
    for(int i=0;i<currentAssignmentSolutions.size();i++)
    {
        if(currentAssignmentSolutions[i].idOfCourse!=tempId)
        tempAssignmentsolutions.push_back(currentAssignmentSolutions[i]);
    }
    currentAssignmentSolutions=tempAssignmentsolutions;
    updatePosts(tempId);
    updateFiles("course_file.txt");
    updateFiles("assignment_file.txt");
    updateFiles("assignmentSolution_file.txt");
}
void DoctorManagment::updatePosts(int courseId)
{
    string path="posts_file.txt";
    vector<string>v;
    vector<string>posts,messages;
    readFromFile(path,v);
    vector<int>ids;
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        string contentOfPost;
        int id;
        int userId;
        string typeUser;
        int courseId;
        iss>>contentOfPost>>id>>userId>>typeUser>>courseId;
        if(id!=courseId)
        posts.push_back(v[i]);
        else
        ids.push_back(id);

    }
    writeOnFile(path,posts);
    path="messages_file.txt";
    v.clear();
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        string content;
        int sendId;
        int recId;
        string typesend;
        string typerec;
        iss>>content>>sendId>>recId>>typesend>>typerec;
        bool ok=true;
        for(int j=0;j<ids.size();j++)
        {
            if(typerec=="post" && recId==ids[j])
            ok=false;
        }
        if(ok)
        messages.push_back(v[i]);
    }
    writeOnFile(path,messages);
}
void DoctorManagment::reloadDoctors()
{
    string path="doctor_file.txt";
    vector<string>v;
    currentDoctors.clear();
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        Doctor d;
        iss>>d.userName>>d.password>>d.type>>d.numberPhone>>d.email>>d.numberPhone>>d.id;
        currentDoctors.push_back(d);
    }
}
void DoctorManagment::reloadCourses()
{
    int tempId=0;
    string path="course_file.txt";
    vector<string>v;
    currentCourses.clear();
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        Course c;
        iss>>c.doctorname>>c.name>>c.abouWhat>>c.id;
        tempId=max(tempId,c.id);
        if(c.doctorname==currentDoctor.userName)
        currentCourses.push_back(c);
    }
    lastIdCourse=tempId;
}
void DoctorManagment::reloadAssignments()
{
    int tempId=0;
    string path="assignment_file.txt";
    vector<string>v;
    currentAssignments.clear();
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        Assignment a;
        iss>>a.doctorName>>a.question>>a.maxGrade>>a.idOfCourse>>a.idOfAssignment;
        tempId=max(tempId,a.idOfAssignment);
        if(a.doctorName==currentDoctor.userName)
        currentAssignments.push_back(a);
    }
    lastIdAssignment=tempId;
}
void DoctorManagment::reloadAssignmentsolutions()
{
    string path="assignmentsolution_file.txt";
    vector<string>v;
    currentAssignmentSolutions.clear();
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        AssignmentSolution a;
        iss>>a.doctorName>>a.ans>>a.comment>>a.grade>>a.studentID>>a.idOfAssignment>>a.idOfCourse>>a.nameOfStudent;
        if(a.doctorName==currentDoctor.userName)
        currentAssignmentSolutions.push_back(a);
    }
}
void DoctorManagment::reloadTeachers()
{
    vector<string>v;
    currentTeacher.clear();
    string path="teacher_file.txt";
    readFromFile(path,v);
    path="inviteteacher_file.txt";
    vector<string>temp;
    readFromFile(path,temp);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        Teacher t;
        iss>>t.userName>>t.password>>t.type>>t.name>>t.email>>t.use>>t.id;
        bool ok=true;
        for(int j=0;j<temp.size();j++)
        {
            istringstream is(temp[j]);
            int doctorId;
            int teacherId;
            is>>doctorId>>teacherId;
            if(doctorId==currentDoctor.id && teacherId==t.id)
            ok=false;
        }
        if(!ok || t.use!=-1)
        continue;
        currentTeacher.push_back(t);
    }
}
void DoctorManagment::updateFiles(string path)
{
    vector<string>v;
    readFromFile(path,v);
    vector<string>temp;
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        string name;
        iss>>name;
        if(name!=currentDoctor.userName)
        temp.push_back(v[i]);
    }
    if(path=="course_file.txt")
    {
        for(int j=0;j<currentCourses.size();j++)
        temp.push_back(currentCourses[j].info());
    }
    else if(path=="assignment_file.txt")
    {
        for(int j=0;j<currentAssignments.size();j++)
        temp.push_back(currentAssignments[j].info());
    }
    else if(path=="assignmentsolutions_file.txt")
    {
        for(int j=0;j<currentAssignmentSolutions.size();j++)
        temp.push_back(currentAssignmentSolutions[j].info());
    }
    writeOnFile(path,temp);
}
void DoctorManagment::updateAssignmentsolutin(string path,vector<AssignmentSolution>&curr)
{
    vector<string>s;
    for(int i=0;i<curr.size();i++)
    s.push_back(curr[i].info());
    writeOnFile(path,s);
}
void DoctorManagment::updatePostId()
{
    string path="posts_file.txt";
    vector<string>v;
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        string content;
        int id;
        iss>>content>>id;
        lastIdPost=max(id,lastIdPost);
    }
}
void DoctorManagment::updateRegistered(int courseId)
{
    vector<string>v;
    string path="registerescourses_file.txt";
    readFromFile(path,v);
    vector<string>temp;
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        int tempCourseId;
        int studentId;
        iss>>tempCourseId>>studentId;
        if(tempCourseId!=courseId)
        temp.push_back(v[i]);
    }
    writeOnFile(path,temp);
}
