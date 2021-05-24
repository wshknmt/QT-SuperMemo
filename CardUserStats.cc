#include "CardUserStats.h"

CardUserStats::CardUserStats() {

}

std::shared_ptr<Card> CardUserStats::getCardPtr() const {
    return cardPtr_;
}

void CardUserStats::setCardPtr(const std::shared_ptr<Card> &cardPtr) {
    cardPtr_ = cardPtr;
}

QDate CardUserStats::getNextReviewDate() const {
    if (stats_.size() > 0){
        QDate mostRecentDate = QDate(1, 1, 1);
        for (Stat stat : stats_){
            QDate tmpDate = stat.first;
            if (tmpDate > mostRecentDate)
                mostRecentDate = tmpDate;
        }
        return mostRecentDate.addDays(3);
    } else {
        return QDate::currentDate().addDays(2);
    }
}
