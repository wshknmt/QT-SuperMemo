#ifndef USER_H
#define USER_H

#include <QObject>
#include "Course.h"

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    explicit User(QString name, QObject *parent = nullptr);
    int getCoursesListSize();
    Course* getCourse(int i);
    QString getName();
    void printCourses();
    QList <Course*> &getCoursesList();
private:
    QList <Course*> coursesList;
    QString name;

signals:

};

#endif // USER_H
