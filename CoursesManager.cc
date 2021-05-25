#include "CoursesManager.h"
#include <QMutex>
#include <fstream>

static QMutex mutexCoursesManager;
CoursesManager* CoursesManager::instancePtr_ = nullptr;

CoursesManager::CoursesManager(){
}

CoursesManager& CoursesManager::getInstance(){
    if (!instancePtr_){
        mutexCoursesManager.lock();
        if (!instancePtr_)
            instancePtr_ = new CoursesManager();
        mutexCoursesManager.unlock();
    }
    return *instancePtr_;
}

std::shared_ptr<Course> CoursesManager::loadCourseFromFile(std::string fileName){
    std::ifstream input;
    input.open(fileName);
    std::string courseName;
    input >> courseName;
    input.close();
    return std::shared_ptr<Course>(new Course(QString::fromStdString(courseName)));
}

std::vector<std::shared_ptr<Course>>& CoursesManager::getCoursesVec(){
    return coursesVec_;
}

void CoursesManager::addCourse(std::shared_ptr<Course> coursePtr){
    for (std::shared_ptr<Course> cp : coursesVec_){
        if (cp == coursePtr)
            return;
    }
    coursesVec_.push_back(coursePtr);
}
void CoursesManager::addCourse(std::string fileName){

}
void CoursesManager::addCourses(std::vector<std::shared_ptr<Course>>& courses){

}
void CoursesManager::addCourses(std::vector<std::string>& fileNames){

}
void CoursesManager::deleteCourse(std::shared_ptr<Course> course){

}
void CoursesManager::deleteCourse(std::string fileName){

}
void CoursesManager::deleteCourses(std::vector<std::shared_ptr<Course>>& courses){

}
void CoursesManager::deleteCourses(std::vector<std::string>& fileNames){

}
unsigned int CoursesManager::getCoursesNumber() const{
    return coursesVec_.size();
}
