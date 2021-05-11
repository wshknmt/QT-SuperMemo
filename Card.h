#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QtMultimedia/QSound>
#include <QImage>
#include <QPixmap>
#include <QDate>

class Card : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString question READ question)
    Q_PROPERTY(QString answer READ answer)
    Q_PROPERTY(QPixmap image READ image)
    Q_PROPERTY(QString soundPath READ soundPath)


public:
    explicit Card(QString q, QString a, QPixmap i, QString s, QDate r);
    QString question() const;
    QString answer() const;
    QPixmap image() const;
    QString soundPath() const;
    QDate repeatDate();
    void setRepeatDate(QDate repeatDate);

signals:

private:
    QString m_question;
    QString m_answer;
    QPixmap m_image;
    QString m_soundPath;
    QDate m_repeatDate;

};

#endif // CARD_H
