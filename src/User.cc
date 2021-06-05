/*
 * File name: User.cc
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class representing user account.
 */

#include "User.h"

User::User() : name_("default_user") {}

User::User(QString name) : name_(name) {}

QString User::getName() const {
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
    if(bWrite) {
        file.write((char*)&name_, sizeof(name_));
        file.write((char*)&coursesManager_, sizeof(coursesManager_));
        file.write((char*)&userStats_, sizeof(userStats_));
    } else {
        return;
    }
}
