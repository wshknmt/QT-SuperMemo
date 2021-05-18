#include "User.h"

User::User(QObject *parent) : QObject(parent)
{
    name = "default_user";
}

User::User(QString name, QObject *parent) : QObject(parent)
{
    this->name = name;
}
int User::getCoursesListSize()
{
    return coursesList.size();
}

Course* User::getCourse(int i)
{
    return coursesList[i];
}

void User::printCourses()
{
    for(int i = 0; i < coursesList.size(); i++)
    {
        coursesList[i]->printCourse();
    }
}
QList <Course*> &User::getCoursesList()
{
    return coursesList;
}
