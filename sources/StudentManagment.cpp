#include "StudentManagment.h"

void StudentManagment::logIn()
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
        if(check(name,password,"student"))
        {
            cout<<"please try again later until you are accepted by the admin"<<endl;
            ok=true;
            break;
        }
        for(int i=0;i<currentStudents.size();i++)
        {
            if(currentStudents[i].userName==name && currentStudents[i].password==password)
            {
                currentStudent.userName=name;
                currentStudent.password=password;
                currentStudent.email=currentStudents[i].email;
                currentStudent.name=currentStudents[i].name;
                currentStudent.id=i+1;
                ok=false;
                break;
            }
        }
        if(ok)
        cout<<"Invalid Username or password,please try again"<<endl;
    }
    reloadCourses();
    reloadAssignment();
    reloadAssignmentSolution();
    menuOfStudent();
}
void StudentManagment::signUp()
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
        for(int i=0;i<currentStudents.size();i++)
        {
            if(currentStudents[i].userName==name)
            {
                ok=true;
                break;
            }
        }
        if(ok)
        cout<<"Invalid Username or password,please try again"<<endl;
    }
    currentStudent.userName=name;
    cout<<"enter your password: "<<endl;
    cin>>currentStudent.password;
    cout<<"enter your  name: "<<endl;
    cin>>currentStudent.name;
    cout<<"enter your email: "<<endl;
    cin>>currentStudent.email;
    currentStudent.id=currentStudents.size()+1;
    addToFile("admin_file.txt",currentStudent.info());
    cout<<"Please wait until you are accepted by the admin"<<endl;
}
void StudentManagment::menuOfStudent()
{
    cout<<"1_register on course"<<endl;
    cout<<"2_list my courses"<<endl;
    cout<<"3_view course"<<endl;
    cout<<"4_grades report"<<endl;
    cout<<"5_view messages to me"<<endl;
    cout<<"6_view messages from me"<<endl;
    cout<<"7_send message"<<endl;
    cout<<"8_back"<<endl;
    int choice;
    bool ok=true;
    while(ok)
    {
        cout<<"please enter your choice:"<<endl;
        cin>>choice;
        if(choice>=1 && choice<=8)
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    ok=true;
    if(choice==1)
    {
        updateCourses();
        registerOnCourse();
    }
    else if(choice==2)
    listMyCourses();
    else if(choice==3)
    {
        if(listMyCourses())
        {
            int num;
            bool ok=true;
            while(ok)
            {
                cout<<"enter the number of course"<<endl;
                cin>>num;
                if(num>=1 && num<=registeredCourses.size())
                ok=false;
                if(ok)
                cout<<"invalid input please try again"<<endl;
            }
            viewCourse(registeredCourses[num-1].id);
        }
    }
    else if(choice==4)
    gradesReport();
    else if(choice==5)
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
            if(rec==currentStudent.id && typerec=="student")
            {
                cout<<typesend<<" with id "<<send<<" sent message:"<<stringWithoutComma(message)<<endl;
                coun++;
            }
        }
        if(!coun)
        cout<<"there are no messages to you :("<<endl;
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
            if(send==currentStudent.id && typesend=="student")
            {
                cout<<"you send to "<<typerec<<" with id "<<rec<<" and your message :"<<stringWithoutComma(message)<<endl;
                coun++;
            }
        }
        if(!coun)
        cout<<"there are no messages from you :("<<endl;
    }
    else if(choice==7)
    sendMessage();
    else
    ok=false;
    if(ok)
    menuOfStudent();
}
void StudentManagment::sendMessage()
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
        allUsers(path,v);
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
        temp+=to_string(currentStudent.id);
        temp+=' ';
        temp+=to_string(id);
        temp+=' ';
        temp+="student";
        temp+=' ';
        temp+="doctor";
        addToFile("messages_file.txt",temp);
    }
    else if(choice==2)
    {
        vector<pair<string,int>>v;
        string path="student_file.txt";
        allUsers(path,v,currentStudent.id);
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
        temp+=to_string(currentStudent.id);
        temp+=' ';
        temp+=to_string(id);
        temp+=' ';
        temp+="student";
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
        temp+=to_string(currentStudent.id);
        temp+=' ';
        temp+=to_string(id);
        temp+=' ';
        temp+="student";
        temp+=' ';
        temp+="teacher";
        addToFile("messages_file.txt",temp);
    }
    else
    ok=false;
    if(ok)
    sendMessage();
}
void StudentManagment::gradesReport()
{
    for(int i=0;i<currentAssignmentsolutions.size();i++)
    {
        cout<<i+1<<"_the id of course:"<<currentAssignmentsolutions[i].idOfCourse<<endl
        <<"the id of the assignment:"<<currentAssignmentsolutions[i].idOfAssignment<<endl
        <<"your mark for this assignment:"<<currentAssignmentsolutions[i].grade<<endl;
    }
    if(!currentAssignmentsolutions.size())
    cout<<"there are no solutions :("<<endl;
}
void StudentManagment::registerOnCourse()
{
    bool ok=true;
    for(int i=0;i<unRegisteredCourses.size();i++)
    {
        cout<<i+1<<"_the name of the course:"<<stringWithComma(unRegisteredCourses[i].name)<<endl
        <<"the doctor of the course is:"<<stringWithoutComma(unRegisteredCourses[i].doctorname)<<endl
        <<"information about course:"<<stringWithComma(unRegisteredCourses[i].abouWhat)<<endl;
        ok=false;
    }
    if(ok)
    {
        cout<<"ther are no courses :("<<endl;
        return;
    }
    int choice;
    ok=true;
    while(ok)
    {
        cout<<"enter the number of the course"<<endl;
        cin>>choice;
        if(choice>=1 && choice<=unRegisteredCourses.size())
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    registeredCourses.push_back(unRegisteredCourses[choice-1]);
    string info=to_string(currentStudent.id);
    info+=' ';
    info+=to_string(unRegisteredCourses[choice-1].id);
    unRegisteredCourses.erase(unRegisteredCourses.begin()+choice-1);
    addToFile("registeredcourses_file.txt",info);
    reloadAssignment();
}
bool StudentManagment::listMyCourses()
{
    bool ok=true;
    for(int i=0;i<registeredCourses.size();i++)
    {
        cout<<i+1<<"_the name of the course:"<<stringWithoutComma(registeredCourses[i].name)<<endl
        <<"the doctor of the course is:"<<stringWithoutComma(registeredCourses[i].doctorname)<<endl
        <<"information about course:"<<stringWithoutComma(registeredCourses[i].abouWhat)<<endl;
        ok=false;
    }
    if(ok)
    cout<<"ther are no registeredcourses :("<<endl;
    return !ok;
}
void StudentManagment::viewCourse(int courseId)
{
    cout<<"1_list assignmnent"<<endl;
    cout<<"2_set answer"<<endl;
    cout<<"3_log out from this course"<<endl;
    cout<<"4_create post"<<endl;
    cout<<"5_list post"<<endl;
    cout<<"6_view post"<<endl;
    cout<<"7_back"<<endl;
    int choice;
    bool ok=true;
    while(ok)
    {
        cout<<"enter your choice:"<<endl;
        cin>>choice;
        if(choice>=1 & choice<=7)
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    ok=true;
    if(choice==1)
    listAssignemnt(courseId);
    else if(choice==2)
    {
        int counOfAssignmnet=listAssignemnt(courseId);
        if(counOfAssignmnet)
        {
            int choice=0;
            bool ok=true;
            while(ok)
            {
                cout<<"enter the number of the assignment:"<<endl;
                cin>>choice;
                if(choice>=1 && choice<=counOfAssignmnet)
                ok=false;
                if(ok)
                cout<<"invalid input please try again"<<endl;
            }
            int num=1;
            int assignmentId=0;
            string doctorName;
            for(int i=0;i<currentAssignments.size();i++)
            {
                if(currentAssignments[i].idOfCourse==courseId)
                {
                    if(num==choice)
                    {
                        assignmentId=currentAssignments[i].idOfAssignment;
                        doctorName=currentAssignments[i].doctorName;
                        break;
                    }
                    num++;
                }
            }
            setAnswer(assignmentId,courseId,doctorName);
        }
    }
    else if(choice==3)
    {
        logOutFromThisCourse(courseId);
        ok=false;
    }
    else if(choice==4)
    createPost(courseId);
    else if(choice==5)
    listPost(courseId);
    else if(choice==6)
    {
        vector<string>posts=listPost(courseId);
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
    viewCourse(courseId);
}
void StudentManagment::createPost(int courseId)
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
    temp+=to_string(currentStudent.id);
    temp+=' ';
    temp+="student";
    temp+=' ';
    temp+=to_string(courseId);
    addToFile("posts_file.txt",temp);
}
vector<string> StudentManagment::listPost(int courseId)
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
void StudentManagment::viewPost(string post)
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
            iss>>content>>userId>>temppostId>>typeUser>>typePost;
            cout<<i+1<<"_the "<<typeUser<<" with the id "<<userId<<':'<<stringWithoutComma(content)<<endl;
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
        temp+=to_string(currentStudent.id);
        temp+=' ';
        temp+=to_string(postId);
        temp+=' ';
        temp+="student";
        temp+=' ';
        temp+="post";
        addToFile(path,temp);
    }
    else
    ok=false;
    if(ok)
    viewPost(post);
}
void StudentManagment::listComment(int postId,vector<string>&comments)
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
void StudentManagment::logOutFromThisCourse(int courseId)
{
    int pos=0;
    for(int i=0;i<registeredCourses.size();i++)
    {
        if(registeredCourses[i].id==courseId)
        {
            pos=i;
            break;
        }
    }
    unRegisteredCourses.push_back(registeredCourses[pos]);
    registeredCourses.erase(registeredCourses.begin()+pos);
    vector<Assignment>tempAssignment;
    vector<AssignmentSolution>tempAssignmentSolution;
    for(int i=0;i<currentAssignments.size();i++)
    {
        if(currentAssignments[i].idOfCourse!=courseId)
        tempAssignment.push_back(currentAssignments[i]);
    }
    currentAssignments=tempAssignment;
    for(int i=0;i<currentAssignmentsolutions.size();i++)
    {
        if(currentAssignmentsolutions[i].idOfCourse!=courseId)
        tempAssignmentSolution.push_back(currentAssignmentsolutions[i]);
    }
    currentAssignmentsolutions=tempAssignmentSolution;
    updateRegisteredCoursesFile(courseId);
    updataAssignmentSolution(courseId);
}
void StudentManagment::setAnswer(int assignmentId,int courseId,string doctorName)
{
    bool ok=true;
    int pos=0;
    for(int i=0;i<currentAssignmentsolutions.size();i++)
    {
        if(currentAssignmentsolutions[i].idOfAssignment==assignmentId)
        {
            ok=false;
            pos=i;
            break;
        }
    }
    if(ok)
    {
        string answer;
        cout<<"enter your answer:"<<endl;
        cin.ignore();
        getline(cin,answer);
        stringWithComma(answer);
        AssignmentSolution temp;
        temp.ans=answer;
        temp.comment="empty";
        temp.doctorName=doctorName;
        temp.grade=-1;
        temp.idOfAssignment=assignmentId;
        temp.idOfCourse=courseId;
        temp.nameOfStudent=currentStudent.userName;
        temp.studentID=currentStudent.id;
        currentAssignmentsolutions.push_back(temp);
        addToFile("assignmentsolution_file.txt",temp.info());
    }
    else
    {
        cout<<"you have an old answer, do you want to change your answer"<<endl;
        cout<<"1_YES"<<endl;
        cout<<"2_NO"<<endl;
        int choice;
        bool ok=true;
        while(ok)
        {
            cout<<"enter your choice:"<<endl;
            cin>>choice;
            if(choice>=1 && choice<=2)
            ok=false;
            if(ok)
            cout<<"invalid input please try again"<<endl;
        }
        if(choice==1)
        {
            string answer;
            cout<<"enter your answer"<<endl;
            cin.ignore();
            getline(cin,answer);
            stringWithComma(answer);
            int id=0;
            for(int i=0;i<currentAssignmentsolutions.size();i++)
            {
                if(currentAssignmentsolutions[i].idOfAssignment==assignmentId)
                {
                    currentAssignmentsolutions[i].ans=answer;
                    currentAssignmentsolutions[i].comment="empty";
                    currentAssignmentsolutions[i].grade=-1;
                    id=currentAssignmentsolutions[i].idOfCourse;
                }
            }
            vector<string>v;
            string path="assignmentsolution_file.txt";
            readFromFile(path,v);
            vector<string>temp;
            bool ok=true;
            for(int i=0;i<v.size();i++)
            {
                istringstream iss(v[i]);
                AssignmentSolution tempa;
                iss>>tempa.doctorName>>tempa.ans>>tempa.comment>>tempa.grade>>tempa.studentID>>tempa.idOfAssignment>>tempa.idOfCourse;
                if(tempa.studentID!=currentStudent.id)
                temp.push_back(v[i]);
                else if(ok)
                {
                    ok=false;
                    for(int j=0;j<currentAssignmentsolutions.size();j++)
                    temp.push_back(currentAssignmentsolutions[j].info());
                }
            }
            writeOnFile("assignmentsolution_file.txt",temp);
        }
    }
}
int StudentManagment::listAssignemnt(int courseId)
{
    int coun=0;
    int id=1;
    for(int i=0;i<currentAssignments.size();i++)
    {
        if(currentAssignments[i].idOfCourse==courseId)
        {
            cout<<id<<"_question:"<<stringWithoutComma(currentAssignments[i].question)<<endl
            <<"max grade:"<<currentAssignments[i].maxGrade<<endl;
            coun++;
            id++;
        }
    }
    if(!coun)
    cout<<"there are no Assignment in this course :("<<endl;
    return coun;
}
void StudentManagment::reloadCourses()
{
    unRegisteredCourses.clear();
    registeredCourses.clear();
    vector<string>v,reg;
    string path="course_file.txt";
    readFromFile(path,v);
    path="registeredcourses_file.txt";
    readFromFile(path,reg);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        Course c;
        iss>>c.doctorname>>c.name>>c.abouWhat>>c.id;
        bool ok=true;
        for(int j=0;j<reg.size();j++)
        {
            istringstream is(reg[j]);
            int id1,id2;
            is>>id1>>id2;
            if(currentStudent.id==id1 && id2==c.id)
            ok=false;
        }
        if(ok)
        unRegisteredCourses.push_back(c);
        else
        registeredCourses.push_back(c);
    }
}
void StudentManagment::reloadStudents()
{
    string path="student_file.txt";
    vector<string>v;
    currentStudents.clear();
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        Student s;
        iss>>s.userName>>s.password>>s.type>>s.name>>s.email>>s.id;
        currentStudents.push_back(s);
    }
}
void StudentManagment::reloadAssignment()
{
    string path="assignment_file.txt";
    currentAssignments.clear();
    vector<string>v;
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        Assignment temp;
        iss>>temp.doctorName>>temp.question>>temp.maxGrade>>temp.idOfCourse>>temp.idOfAssignment>>temp.numberOfStudent;
        for(int j=0;j<registeredCourses.size();j++)
        {
            if(registeredCourses[j].id==temp.idOfCourse)
            currentAssignments.push_back(temp);
        }
    }
}
void StudentManagment::reloadAssignmentSolution()
{
    string path="assignmentsolution_file.txt";
    currentAssignmentsolutions.clear();
    vector<string>v;
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        AssignmentSolution temp;
        iss>>temp.doctorName>>temp.ans>>temp.comment>>temp.grade>>temp.studentID>>temp.idOfAssignment>>temp.idOfCourse>>temp.nameOfStudent;
        for(int j=0;j<registeredCourses.size();j++)
        {
            if(registeredCourses[j].id==temp.idOfCourse)
            currentAssignmentsolutions.push_back(temp);
        }
    }
}
void StudentManagment::updateCourses()
{
    unRegisteredCourses.clear();
    vector<string>v;
    string path="course_file.txt";
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        Course c;
        iss>>c.doctorname>>c.name>>c.abouWhat>>c.id;
        bool ok=true;
        for(int j=0;j<registeredCourses.size();j++)
        {
            if(c.id==registeredCourses[j].id)
            {
                ok=false;
                break;
            }
        }
        if(ok)
        unRegisteredCourses.push_back(c);
    }
}
void StudentManagment::updateRegisteredCoursesFile(int courseId)
{
    vector<string>v;
    string path="registeredcourses_file.txt";
    readFromFile(path,v);
    int pos=0;
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        int id1;
        int id2;
        iss>>id1>>id2;
        if(id1==currentStudent.id && id2==courseId)
        {
            pos=i;
            break;
        }
    }
    v.erase(v.begin()+pos);
    writeOnFile("registeredcourses_file.txt",v);
}
void StudentManagment::updataAssignmentSolution(int courseId)
{
    vector<string>v;
    string path="assignmentsolution_file.txt";
    readFromFile(path,v);
    vector<string>temp;
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        AssignmentSolution tempa;
        iss>>tempa.doctorName>>tempa.ans>>tempa.comment>>tempa.grade>>tempa.studentID>>tempa.idOfAssignment>>tempa.idOfCourse;
        if(tempa.studentID!=currentStudent.id || tempa.idOfCourse!=courseId)
        temp.push_back(v[i]);
    }
    writeOnFile("assignmentsolution_file.txt",temp);
}
void StudentManagment::updatePostId()
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
