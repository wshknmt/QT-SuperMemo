/*
 * File name: CoursesManager.cc
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class representing course management module.
 */

#include "CoursesManager.h"

CoursesManager::CoursesManager() : coursesCounter_(0) {}

CoursesManager::~CoursesManager() {
    for (Course* cPtr : coursesList_)
        delete cPtr;
}

QList<Course*> &CoursesManager::getCoursesList() {
    return coursesList_;
}

Course* CoursesManager::createCourse() {
    Course *course = new Course();
    coursesList_.append(course);
    coursesCounter_++;
    return course;
}
Course* CoursesManager::createCourse(QString name) {
    Course *course = new Course(name);
    coursesList_.append(course);
    coursesCounter_++;
    return course;
}

void CoursesManager::addCourse(Course *course) {
    coursesList_.append(course);
    coursesCounter_++;
}

void CoursesManager::deleteCourse(int courseNumber) {
    coursesList_.removeAt(courseNumber);
    coursesCounter_--;
}
int CoursesManager::getCoursesNumber() const {
    return coursesList_.size();
}

Course* CoursesManager::getCourse(int i) const {
    return coursesList_[i];
}