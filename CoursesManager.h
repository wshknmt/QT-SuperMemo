#ifndef COURSESMANAGER_H
#define COURSESMANAGER_H

#include "Course.h"


class CoursesManager {
public:
    CoursesManager();
    QList <Course*> &getCoursesList();
    Course* createCourse();
    Course* createCourse(QString name);
    void addCourse(Course *course);
    void addCourse(std::string fileName);
    //void addCourses(std::vector<std::shared_ptr<Course>>& courses);
   // void addCourses(std::vector<std::string>& fileNames);
    void deleteCourse(int courseNumber);
    //void deleteCourse(std::string fileName);
    //void deleteCourses(std::vector<std::shared_ptr<Course>>& courses);
    //void deleteCourses(std::vector<std::string>& fileNames);
    int getCoursesNumber();
    Course* getCourse(int i);
    void printCourses();

private:

    QList <Course*> coursesList_;
    int coursesCounter_;
};

#endif // COURSESMANAGER_H
