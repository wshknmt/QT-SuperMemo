#ifndef USERSTATS_H
#define USERSTATS_H

#include <QDate>

#include "AnswerType.h"

typedef std::pair<QDate, AnswerType> Stat;

class UserStats
{
public:
    UserStats();
    void addStat(Stat stat);
    int getSize();
    void updateCounters();
    int getGoodCounter();
    int getMixedCounter();
    int getWrongCounter();
private:
    QList <Stat> stats_;
    int goodCounter_;
    int mixedCounter_;
    int wrongCounter_;
};

#endif // USERSTATS_H
