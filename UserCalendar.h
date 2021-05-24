#ifndef USERCALENDAR_H
#define USERCALENDAR_H

#include <QDate>
#include <vector>
#include <memory>

#include "Course.h"

typedef std::pair<QDate, std::shared_ptr<Course>> Review;

class UserCalendar{
public:
    UserCalendar();
private:
    std::vector<Review> reviews_;
};

#endif // USERCALENDAR_H
