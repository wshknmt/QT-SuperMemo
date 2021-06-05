/*
 * File name: CoursesManager.h
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class representing course management module.
 */

#ifndef COURSESMANAGER_H
#define COURSESMANAGER_H

#include "Course.h"

class CoursesManager {
public:
    CoursesManager();
    QList<Course*> &getCoursesList();
    Course* createCourse();
    Course* createCourse(QString name);
    void addCourse(Course *course);
    void deleteCourse(int courseNumber);
    int getCoursesNumber() const;
    Course* getCourse(int i) const;

private:
    QList <Course*> coursesList_;
    int coursesCounter_;
};

#endif // COURSESMANAGER_H
