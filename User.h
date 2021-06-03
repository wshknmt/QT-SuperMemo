#ifndef USER_H
#define USER_H

#include <QObject>
#include <fstream>
#include "Course.h"
#include "CoursesManager.h"
#include "UserStats.h"


class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    explicit User(QString name, QObject *parent = nullptr);
    QString getName();
    void print();
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

signals:

};

#endif // USER_H
