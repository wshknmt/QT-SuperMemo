#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QtMultimedia/QSound>
#include <QImage>

class Card : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString question READ question)
    Q_PROPERTY(QString answer READ answer)
   // Q_PROPERTY(QImage image READ image)
   // Q_PROPERTY(QSound sound READ sound)


public:
    explicit Card(QString q, QString a/*, QImage i, QSound &s*/);
    QString question() const;
    QString answer() const;
    //QImage image() const;
    //QSound sound() const;

signals:

private:
    QString m_question;
    QString m_answer;
    //QImage m_image;
    //QSound m_sound;

};

#endif // CARD_H
