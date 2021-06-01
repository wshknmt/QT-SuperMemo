#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QtMultimedia/QSound>
#include <QImage>
#include <QPixmap>
#include <QDate>

class Card : public QObject {
    Q_OBJECT
    /*Q_PROPERTY(QString question READ getQuestion)
    Q_PROPERTY(QString answer READ getAnswer)
    Q_PROPERTY(QPixmap image READ getImage)
    Q_PROPERTY(QString soundPath READ getSoundPath)*/

public:
    explicit Card(QString q, QString a, QPixmap i, QString s, QDate r);
    QString getQuestion() const;
    QString getAnswer() const;
    QPixmap getImage() const;
    QString getSoundPath() const;
    QDate getRepeatDate();
    void setRepeatDate(QDate repeatDate);
    void printCard();

signals:

private:
    QString question_;
    QString answer_;
    QPixmap image_;
    QString soundPath_;
    QDate repeatDate_;

};

#endif // CARD_H
