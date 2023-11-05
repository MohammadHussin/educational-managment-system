#include "LibrarySystem.h"

void librarySystem::reload()
{
    newDoctor.reloadDoctors();
    newStudent.reloadStudents();
    newTeacher.reloadTeachers();
}
void librarySystem::run()
{
    reload();
    int choice=menuOfLogOrSign();
    if(choice==1)
    {
        int choiceOfLog=menuOfLog();
        if(choiceOfLog==1)
        newDoctor.logIn();
        else if(choiceOfLog==2)
        newStudent.logIn();
        else if(choiceOfLog==3)
        newTeacher.logIn();
        else
        newAdmin.logIn();
    }
    else if(choice==2)
    {
        int choiceOfSign=menuOfSign();
        if(choiceOfSign==1)
        newDoctor.signUp();
        else if(choiceOfSign==2)
        newStudent.signUp();
        else
        newTeacher.signUp();
    }
    else
    return;
    run();
}
