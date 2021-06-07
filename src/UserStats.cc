/*
 * File name: UserStats.cc
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class representing user's statistics in all courses.
 */

#include "UserStats.h"

UserStats::UserStats() : goodCounter_(0), mixedCounter_(0), wrongCounter_(0) {}

void UserStats::addStat(Stat stat) {
    stats_.append(stat);
}

int UserStats::getSize() const {
    return stats_.size();
}

Stat UserStats::getStat(int index) const {
    return stats_[index];
}

void UserStats::updateCounters() {
    for(int i=0; i < getSize(); ++i) {
        if(stats_[i].second == AnswerType::GOOD) ++goodCounter_;
        else if(stats_[i].second == AnswerType::MIXED) ++mixedCounter_;
        else if(stats_[i].second == AnswerType::WRONG) ++wrongCounter_;
    }
}

int UserStats::getGoodCounter() const {
    return goodCounter_;
}

int UserStats::getMixedCounter() const {
    return mixedCounter_;
}

int UserStats::getWrongCounter() const {
    return wrongCounter_;
}
