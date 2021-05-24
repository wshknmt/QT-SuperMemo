#ifndef COURSEPROGRESS_H
#define COURSEPROGRESS_H

#include <memory>
#include <vector>

#include "Course.h"
#include "CardUserStats.h"

class CourseProgress {
public:
    CourseProgress(std::shared_ptr<Course> coursePtr);

private:
    std::shared_ptr<Course> coursePtr_;
    std::vector<std::shared_ptr<CardUserStats>> cardsStats_;
};

#endif // COURSEPROGRESS_H
