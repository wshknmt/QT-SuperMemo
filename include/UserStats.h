/*
 * File name: UserStats.h
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class representing user's statistics in all courses.
 */

#ifndef USERSTATS_H
#define USERSTATS_H

#include <QDate>

#include "AnswerType.h"

typedef std::pair<QDate, AnswerType> Stat;

class UserStats {
public:
    UserStats();
    void addStat(Stat stat);
    int getSize() const;
    Stat getStat(int index) const;
    void updateCounters();
    int getGoodCounter() const;
    int getMixedCounter() const;
    int getWrongCounter() const; 

private:
    QList<Stat> stats_;
    int goodCounter_;
    int mixedCounter_;
    int wrongCounter_;
};

#endif // USERSTATS_H
