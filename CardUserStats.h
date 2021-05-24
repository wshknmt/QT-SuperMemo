#ifndef CARDUSERSTATS_H
#define CARDUSERSTATS_H

#include "AnswerType.h"
#include "Card.h"
#include <vector>
#include <memory>
#include <QDate>

typedef std::pair<QDate, AnswerType> Stat;

class CardUserStats{
public:
    CardUserStats();
    std::shared_ptr<Card> getCardPtr() const;
    void setCardPtr(const std::shared_ptr<Card> &cardPtr);
    QDate getNextReviewDate() const;

private:
    std::shared_ptr<Card> cardPtr_;
    std::vector<Stat> stats_;
};

#endif // CARDUSERSTATS_H
