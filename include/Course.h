/*
 * File name: Course.h
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class representing one course.
 */

#ifndef COURSE_H
#define COURSE_H

// #include <QAbstractTableModel>
// #include <QModelIndex>
// #include <QVariant>

#include "Card.h"

class Course {
public:
    Course(QString n);
    Course();
    ~Course();
    void addCardToRepeat(Card* card);
    void addCardRepeated(Card* card);
    void removeFirstCardToRepeat();
    void removeFirstCardRepeated();
    int getCardsCounter() const;
    Card* getFirstCardToRepeat() const;
    Card* getCardToRepeat(int number) const;
    Card* getCardRepeated(int number) const;
    int getSizeCardsToRepeat() const;
    int getSizeCardsRepeated() const;
    void incrementCardsCounter();
    void decrementCardsCounter();
    QString getName() const;
    bool isEqualToCurrentDate(QDate date) const;
    void checkCards();
    void simulateTime(qint64 days);
    void countProgress();
    int getProgress() const;
    void reviewRequest();

private:
    QList <Card*> cardsToRepeat_;
    QList <Card*> cardsRepeated_;
    QString name_;
    int progress_;
    int cardsCounter_;
};

#endif // COURSE_H
