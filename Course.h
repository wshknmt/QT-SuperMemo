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
    explicit Course(QString n, QObject *parent = nullptr);
    explicit Course(QObject *parent = nullptr);
    void addCardToRepeat(Card* card);
    void addCardRepeated(Card* card);
    void removeFirstCardToRepeat();
    void removeFirstCardRepeated();
    int getCardsCounter();
    Card* getFirstCardToRepeat();
    int getSizeCardsToRepeat();
    int getSizeCardsRepeated();
    void incrementCardsCounter();
    void decrementCardsCounter();
    QString getName();


signals:

private:
    QList <Card*> cardsToRepeat;
    QList <Card*> cardsRepeated;
    QString name;
    int cardsCounter;
};

#endif // COURSE_H
