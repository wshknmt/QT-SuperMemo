#ifndef COURSESMANAGER_H
#define COURSESMANAGER_H

#include <vector>
#include <memory>
#include <string>

#include "Course.h"

class CoursesManager{
public:
    static CoursesManager& getInstance();
    static std::shared_ptr<Course> loadCourseFromFile(std::string fileName);
    std::vector<std::shared_ptr<Course>>& getCoursesVec();
    void addCourse(std::shared_ptr<Course> course);
    void addCourse(std::string fileName);
    void addCourses(std::vector<std::shared_ptr<Course>>& courses);
    void addCourses(std::vector<std::string>& fileNames);
    void deleteCourse(std::shared_ptr<Course> course);
    void deleteCourse(std::string fileName);
    void deleteCourses(std::vector<std::shared_ptr<Course>>& courses);
    void deleteCourses(std::vector<std::string>& fileNames);
    unsigned int getCoursesNumber() const;

private:
    CoursesManager();
    static CoursesManager* instancePtr_;
    std::vector<std::shared_ptr<Course>> coursesVec_;

};

#endif // COURSESMANAGER_H
