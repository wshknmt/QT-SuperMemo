#ifndef COURSE_H
#define COURSE_H

#include <QObject>
#include "Card.h"

class Course : public QObject
{
    Q_OBJECT
public:
    explicit Course(QObject *parent = nullptr);

signals:

private:
    QList <Card> cardsToRepeat;
    QList <Card> cardsRepeated;

};

#endif // COURSE_H
