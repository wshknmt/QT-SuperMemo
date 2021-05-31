#include <QTextStream>
#include "CoursesManager.h"
CoursesManager::CoursesManager() {
    coursesCounter_ = 0;
}

QList <Course*> &CoursesManager::getCoursesList() {
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
void CoursesManager::addCourse(std::string fileName) {

}
void CoursesManager::deleteCourse(int courseNumber) {

}
int CoursesManager::getCoursesNumber() {
    return coursesList_.size();
}

Course* CoursesManager::getCourse(int i) {
    return coursesList_[i];
}

void CoursesManager::printCourses() {
    for(int i = 0; i < coursesList_.size(); i++)
        coursesList_[i]->printCourse();
}
