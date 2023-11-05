#include "TeacherManagment.h"

void TeacherManagment::logIn()
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
        if(check(name,password,"teacher"))
        {
            cout<<"please try again later until you are accepted by the admin"<<endl;
            ok=true;
            break;
        }
        for(int i=0;i<currentTeachers.size();i++)
        {
            if(currentTeachers[i].userName==name && currentTeachers[i].password==password)
            {
                currentTeacher.userName=name;
                currentTeacher.password=password;
                currentTeacher.email=currentTeachers[i].email;
                currentTeacher.name=currentTeachers[i].name;
                currentTeacher.id=currentTeachers[i].id;
                currentTeacher.type=currentTeachers[i].type;
                currentTeacher.use=currentTeachers[i].use;
                ok=false;
                break;
            }
        }
        if(ok)
        cout<<"Invalid Username or password,please try again"<<endl;
    }
    reloadStudents();
    reloadDoctors();
    reloadTeachers();
    if(currentTeacher.use!=-1)
    {
        reloadCourses();
        reloadAssignment();
        reloadAssignmentSolution();
    }
    menuOfTeacher();
}
void TeacherManagment::signUp()
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
        for(int i=0;i<currentTeachers.size();i++)
        {
            if(currentTeachers[i].userName==name)
            {
                ok=true;
                break;
            }
        }
        if(ok)
        cout<<"Invalid Username or password,please try again"<<endl;
    }
    currentTeacher.userName=name;
    cout<<"enter your password: "<<endl;
    cin>>currentTeacher.password;
    cout<<"enter your  name: "<<endl;
    cin>>currentTeacher.name;
    cout<<"enter your email: "<<endl;
    cin>>currentTeacher.email;
    currentTeacher.id=++lastId;
    addToFile("admin_file.txt",currentTeacher.info());
    cout<<"Please wait until you are accepted by the admin"<<endl;
}
void TeacherManagment::menuOfTeacher()
{
    cout<<"1_view invites to me"<<endl;
    cout<<"2_list my courses"<<endl;
    cout<<"3_view course"<<endl;
    cout<<"4_view messages to me"<<endl;
    cout<<"5_view messages from me"<<endl;
    cout<<"6_send message"<<endl;
    cout<<"7_back"<<endl;
    int choice;
    bool ok=true;
    while(ok)
    {
        cout<<"please enter your choice:"<<endl;
        cin>>choice;
        if(choice>=1 && choice<=7)
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    ok=true;
    if(choice==1)
    viewInvitesToMe();
    else if(choice==2)
    listCourses();
    else if(choice==3)
    {
        if(listCourses())
        {
            int choice;
            bool ok=true;
            while(ok)
            {
                cout<<"please enter your choice"<<endl;
                cin>>choice;
                if(choice>=1 && choice<=currentCourses.size())
                ok=false;
                if(ok)
                cout<<"invalid input please try again"<<endl;
            }
            viewCourse(currentCourses[choice-1].id);
        }
    }
    else if(choice==4)
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
            if(rec==currentTeacher.id && typerec=="teacher")
            {
                cout<<typesend<<" with id "<<send<<" sent message:"<<stringWithoutComma(message)<<endl;
                coun++;
            }
        }
        if(!coun)
        cout<<"there are no messages to you :("<<endl;
    }
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
            if(send==currentTeacher.id && typesend=="teacher")
            {
                cout<<"you send to "<<typerec<<" with id "<<rec<<" and your message :"<<stringWithoutComma(message)<<endl;
                coun++;
            }
        }
        if(!coun)
        cout<<"there are no messages from you :("<<endl;
    }
    else if(choice==6)
    sendMessage();
    else
    ok=false;
    if(ok)
    menuOfTeacher();
}
void TeacherManagment::sendMessage()
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
        temp+=to_string(currentTeacher.id);
        temp+=' ';
        temp+=to_string(id);
        temp+=' ';
        temp+="teacher";
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
        temp+=to_string(currentTeacher.id);
        temp+=' ';
        temp+=to_string(id);
        temp+=' ';
        temp+="teacher";
        temp+=' ';
        temp+="student";
        addToFile("messages_file.txt",temp);
    }
    else if(choice==3)
    {
        vector<pair<string,int>>v;
        string path="teacher_file.txt";
        allUsers(path,v,currentTeacher.id);
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
        temp+=to_string(currentTeacher.id);
        temp+=' ';
        temp+=to_string(id);
        temp+=' ';
        temp+="teacher";
        temp+=' ';
        temp+="teacher";
        addToFile("messages_file.txt",temp);
    }
    else
    ok=false;
    if(ok)
    sendMessage();
}
void TeacherManagment::viewCourse(int courseId)
{
    cout<<"1_list assignment"<<endl;
    cout<<"2_view assignment"<<endl;
    cout<<"3_create post"<<endl;
    cout<<"4_list post"<<endl;
    cout<<"5_view post"<<endl;
    cout<<"6_back"<<endl;
    int choice;
    bool ok=true;
    while(ok)
    {
        cout<<"please enter your choice"<<endl;
        cin>>choice;
        if(choice>=1 && choice<=6)
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    ok=true;
    if(choice==1)
    listAssignment(courseId);
    else if(choice==2)
    {
        int numberOfAssignment=listAssignment(courseId);
        if(numberOfAssignment)
        {
            int choice;
            bool ok=true;
            while(ok)
            {
                cout<<"please enter your chooice:"<<endl;
                cin>>choice;
                if(choice>=1 && choice<=numberOfAssignment)
                ok=false;
                if(ok)
                cout<<"invalid input please try again"<<endl;
            }
            int coun=1;
            int pos=0;
            for(int i=0;i<currentAssignments.size();i++)
            {
                if(currentAssignments[i].idOfCourse==courseId)
                {
                    if(coun==choice)
                    {
                        pos=i;
                        break;
                    }
                    coun++;
                }
            }
            viewAssignment(courseId,currentAssignments[pos].idOfAssignment);
        }
    }
    else if(choice==3)
    createPost(courseId);
    else if(choice==4)
    listPost(courseId);
    else if(choice==5)
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
void TeacherManagment::createPost(int courseId)
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
    temp+=to_string(currentTeacher.id);
    temp+=' ';
    temp+="teacher";
    temp+=' ';
    temp+=to_string(courseId);
    addToFile("posts_file.txt",temp);
}
void TeacherManagment::viewPost(string post)
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
        temp+=to_string(currentTeacher.id);
        temp+=' ';
        temp+=to_string(postId);
        temp+=' ';
        temp+="teacher";
        temp+=' ';
        temp+="post";
        addToFile(path,temp);
    }
    else
    ok=false;
    if(ok)
    viewPost(post);
}
void TeacherManagment::viewAssignment(int courseId,int AssignmentId)
{
    reloadAssignmentSolution();
    cout<<"1_list solutions"<<endl;
    cout<<"2_view solution"<<endl;
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
    listSolutions(courseId,AssignmentId);
    else if(choice==2)
    {
        int numberOfSolutions=listSolutions(courseId,AssignmentId);
        if(numberOfSolutions)
        {
            int choice;
            bool ok=true;
            while(ok)
            {
                cout<<"please enter your choice:"<<endl;
                cin>>choice;
                if(choice>=1 && choice<=numberOfSolutions)
                ok=false;
                if(ok)
                cout<<"invalid input please try again"<<endl;
            }
            ok=true;
            int coun=1;
            int pos=0;
            for(int i=0;i<currentAssignmentSolutions.size();i++)
            {
                if(currentAssignmentSolutions[i].idOfAssignment==AssignmentId)
                {
                    if(coun==choice)
                    {
                        pos=i;
                        break;
                    }
                    coun++;
                }
            }
            viewSolution(pos);
        }
    }
    else
    ok=false;
    if(ok)
    viewAssignment(courseId,AssignmentId);
}
void TeacherManagment::viewSolution(int numberOfSolution)
{
    cout<<"1_set grade"<<endl;
    cout<<"2_set comment"<<endl;
    cout<<"3_set grade and comment"<<endl;
    cout<<"4_back"<<endl;
    int choice;
    bool ok=true;
    while(ok)
    {
        cout<<"please enter your chocie"<<endl;
        cin>>choice;
        if(choice>=1 && choice<=4)
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    ok=true;
    if(choice==1)
    setGrade(numberOfSolution,currentAssignmentSolutions,false);
    else if(choice==2)
    setComment(numberOfSolution,currentAssignmentSolutions,false);
    else if(choice==3)
    {
        setGrade(numberOfSolution,currentAssignmentSolutions,false);
        setComment(numberOfSolution,currentAssignmentSolutions,false);
    }
    else
    ok=false;
    if(ok)
    viewSolution(numberOfSolution);
}
int TeacherManagment::listSolutions(int courseId,int assignmentId)
{
    int coun=0;
    for(int i=0;i<currentAssignmentSolutions.size();i++)
    {
        if(currentAssignmentSolutions[i].idOfAssignment==assignmentId)
        {
            cout<<coun+1<<"_ studentId"<<currentAssignmentSolutions[i].studentID<<endl
            <<"grade:"<<currentAssignmentSolutions[i].grade<<endl
            <<"answer:"<<stringWithoutComma(currentAssignmentSolutions[i].ans)<<endl;
            coun++;
        }
    }
    if(!coun)
    cout<<"there are no solutions :("<<endl;
    return coun;
}
bool TeacherManagment::listCourses()
{
    bool ok=true;
    for(int i=0;i<currentCourses.size();i++)
    {
        cout<<i+1<<"_doctor name :"<<stringWithoutComma(currentCourses[i].doctorname)<<endl
        <<"courseid: "<<currentCourses[i].id<<endl;
        ok=false;
    }
    if(ok)
    cout<<"there are no courses :("<<endl;
    return !ok;
}
int TeacherManagment::listAssignment(int courseId)
{
    int coun=0;
    for(int i=0;i<currentAssignments.size();i++)
    {
        if(courseId==currentAssignments[i].idOfCourse)
        {
            cout<<coun+1<<"_ AssignmentId:"<<currentAssignments[i].idOfAssignment<<endl
            <<"max grade:"<<currentAssignments[i].maxGrade<<endl
            <<"question:"<<stringWithoutComma(currentAssignments[i].question)<<endl;
            coun++;
        }
    }
    if(!coun)
    cout<<"there are no assignment :("<<endl;
    return coun;
}
void TeacherManagment::viewInvitesToMe()
{
    vector<string>v;
    string path="inviteteacher_file.txt";
    readFromFile(path,v);
    vector<int>temp;
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        int doctorId;
        int teacherId;
        iss>>doctorId>>teacherId;
        if(teacherId==currentTeacher.id)
        temp.push_back(doctorId);
    }
    for(int i=0;i<temp.size();i++)
    cout<<i+1<<"_doctor id:"<<temp[i]<<endl;
    if(!temp.size())
    {
        cout<<"no invites :("<<endl;
        return;
    }
    int choice;
    bool ok=true;
    while(ok)
    {
        cout<<"enter your choice:"<<endl;
        cin>>choice;
        if(choice>=1 && choice<=temp.size())
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    int num;
    cout<<"1_accept"<<endl;
    cout<<"2_reject"<<endl;
    ok=true;
    while(ok)
    {
        cout<<"enter your choice:"<<endl;
        cin>>num;
        if(num>=1 && num<=2)
        ok=false;
        if(ok)
        cout<<"invalid input please try again"<<endl;
    }
    if(num==1)
    {
        currentTeacher.use=temp[choice-1];
        for(int i=0;i<currentTeachers.size();i++)
        {
            if(currentTeacher.id==currentTeachers[i].id)
            currentTeachers[i].use=temp[choice-1];
        }
        reloadCourses();
        updateTeachers();
    }
    int i=0;
    for(;i<v.size();i++)
    {
        istringstream iss(v[i]);
        int doctorId;
        iss>>doctorId;
        if(doctorId==temp[choice-1]);
        break;
    }
    v.erase(v.begin()+i);
    updateInviteTeacher(v);
}
void TeacherManagment::reloadTeachers()
{
    string path="teacher_file.txt";
    vector<string>v;
    currentTeachers.clear();
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        Teacher t;
        iss>>t.userName>>t.password>>t.type>>t.name>>t.email>>t.use>>t.id;
        lastId=max(lastId,t.id);
        currentTeachers.push_back(t);
    }
}
void TeacherManagment::reloadCourses()
{
    string name;
    for(int i=0;i<currentDoctors.size();i++)
    {
        if(currentDoctors[i].id==currentTeacher.use)
        {
            name=currentDoctors[i].userName;
            break;
        }
    }
    vector<string>v;
    string path="course_file.txt";
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        Course c;
        iss>>c.doctorname>>c.name>>c.abouWhat>>c.id;
        if(c.doctorname==name)
        currentCourses.push_back(c);
    }
}
void TeacherManagment::reloadAssignment()
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
        for(int j=0;j<currentCourses.size();j++)
        {
            if(currentCourses[j].id==temp.idOfCourse)
            currentAssignments.push_back(temp);
        }
    }
}
void TeacherManagment::reloadAssignmentSolution()
{
    string path="assignmentsolution_file.txt";
    currentAssignmentSolutions.clear();
    vector<string>v;
    readFromFile(path,v);
    for(int i=0;i<v.size();i++)
    {
        istringstream iss(v[i]);
        AssignmentSolution temp;
        iss>>temp.doctorName>>temp.ans>>temp.comment>>temp.grade>>temp.studentID>>temp.idOfAssignment>>temp.idOfCourse>>temp.nameOfStudent;
        for(int j=0;j<currentCourses.size();j++)
        {
            if(currentCourses[j].id==temp.idOfCourse)
            currentAssignmentSolutions.push_back(temp);
        }
    }
}
void TeacherManagment::reloadStudents()
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
void TeacherManagment::reloadDoctors()
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
void TeacherManagment::updateTeachers()
{
    string path="teacher_file.txt";
    vector<string>v;
    for(int i=0;i<currentTeachers.size();i++)
    v.push_back(currentTeachers[i].info());
    writeOnFile(path,v);
}
void TeacherManagment::updateInviteTeacher(vector<string>v)
{
    string path="inviteteacher_file.txt";
    writeOnFile(path,v);
}
