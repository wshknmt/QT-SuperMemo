#ifndef COURSE_H
#define COURSE_H

#include <QObject>
#include "Card.h"


#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

class Course : public QObject
{
    Q_OBJECT
public:
    explicit Course(QObject *parent = nullptr);
    void addCardToRepeat(Card* card);
    void addCardRepeated(Card* card);
    void removeFirstCardToRepeat();
    void removeFirstCardRepeated();
    int getCardsCounter();
    Card* getFirstCardToRepeat();
    int getSizeCardsToRepeat();
    void incrementCardsCounter();
    void decrementCardsCounter();


signals:

private:
    QList <Card*> cardsToRepeat;
    QList <Card*> cardsRepeated;
    int cardsCounter;

};

#endif // COURSE_H
