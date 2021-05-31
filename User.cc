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
