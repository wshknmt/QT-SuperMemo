/*
 * File name: Card.h
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class representing one question card.
 */

#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QtMultimedia/QSound>
#include <QImage>
#include <QPixmap>
#include <QDate>

class Card {

public:
    Card(QString q, QString a, QString i, QString s, QDate r);
    QString getQuestion() const;
    QString getAnswer() const;
    QString getImagePath() const;
    QString getSoundPath() const;
    QDate getRepeatDate() const;
    void setRepeatDate(QDate repeatDate);

private:
    QString question_;
    QString answer_;
    QString imagePath_;
    QString soundPath_;
    QDate repeatDate_;
};

#endif // CARD_H
