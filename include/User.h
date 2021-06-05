/*
 * File name: User.h
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class representing user account.
 */

#ifndef USER_H
#define USER_H

#include <fstream>

#include "Course.h"
#include "CoursesManager.h"
#include "UserStats.h"


class User{
public:
    explicit User();
    explicit User(QString name);
    QString getName() const;
    void setName(QString n);
    CoursesManager &getCourseManager();
    UserStats &getUserStats();
    void setCourseManager(CoursesManager &cManager);
    void setUserStats(UserStats &uStats);
    void serialize(std::fstream &file, bool bWrite);

private:
    QString name_;
    CoursesManager coursesManager_;
    UserStats userStats_;
};

#endif // USER_H
