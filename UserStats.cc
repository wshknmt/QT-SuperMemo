#include "UserStats.h"

UserStats::UserStats()
{

}

void UserStats::addStat(Stat stat) {
    stats_.append(stat);
}

int UserStats::getSize() {
    return stats_.size();
}
