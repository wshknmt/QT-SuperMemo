#ifndef USER_H
#define USER_H

#include <QObject>
#include <memory>
#include <vector>
#include "Course.h"
#include "CourseProgress.h"
#include "UserCalendar.h"

class User : public QObject{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    explicit User(QString name, QObject *parent = nullptr);
    int getCoursesListSize();
    Course* getCourse(int i);
    QString getName();
    void printCourses();
    QList <Course*> &getCoursesList();
    void setName(QString n);
    void setCoursesList(QList <Course*> &cList);

private:
    QList <Course*> coursesList;
    QString name;
    std::vector<std::shared_ptr<CourseProgress>> userProgressVec_;
    std::shared_ptr<UserCalendar> userCalendarPtr_;

signals:
};

#endif // USER_H
