#ifndef COURSE_H
#define COURSE_H

#include <QObject>
#include "Card.h"


#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

class Course : public QObject {
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
    Card* getCardToRepeat(int number);
    Card* getCardRepeated(int number);
    int getSizeCardsToRepeat();
    int getSizeCardsRepeated();
    void incrementCardsCounter();
    void decrementCardsCounter();
    void printCourse();
    QString getName();
    bool isEqualToCurrentDate(QDate date);
    void checkCards();
    void simulateTime(qint64 days);

signals:

private:
    QList <Card*> cardsToRepeat_;
    QList <Card*> cardsRepeated_;
    QString name_;
    int cardsCounter_;
};

#endif // COURSE_H
