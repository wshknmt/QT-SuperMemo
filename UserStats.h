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
private:
    QList <Stat> stats_;
};

#endif // USERSTATS_H
