#include "User.h"

User::User(QObject *parent) : QObject(parent) {
    name_ = "default_user";
}

User::User(QString name, QObject *parent) : QObject(parent) {
    this->name_ = name;
}

void User::print() {
    coursesManager_.printCourses();
}

QString User::getName() {
    return name_;
}

void User::setName(QString n) {
    name_ = n;
}

CoursesManager &User::getCourseManager() {
    return coursesManager_;
}

UserStats &User::getUserStats() {
    return userStats_;
}

void User::setCourseManager(CoursesManager &cManager) {
    coursesManager_ = cManager;
}

void User::setUserStats(UserStats &uStats) {
    userStats_ = uStats;
}
void User::serialize(std::fstream &file, bool bWrite) {
    //https://stackoverflow.com/questions/32832604/reading-and-writing-classes-with-pointers-to-binary-files-in-c
        if (bWrite) {
            file.write((char*)&name_, sizeof(name_));
            file.write((char*)&coursesManager_, sizeof(coursesManager_));
            file.write((char*)&userStats_, sizeof(userStats_));

        }
        else {
           return;
        }

}
