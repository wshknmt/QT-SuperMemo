#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QtMultimedia/QSound>
#include <QImage>
#include <QPixmap>

class Card : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString question READ question)
    Q_PROPERTY(QString answer READ answer)
    Q_PROPERTY(QPixmap image READ image)
    Q_PROPERTY(QString soundPath READ soundPath)


public:
    explicit Card(QString q, QString a, QPixmap i, QString s);
    QString question() const;
    QString answer() const;
    QPixmap image() const;
    QString soundPath() const;
    //QSound sound() const;

signals:

private:
    QString m_question;
    QString m_answer;
    QPixmap m_image;
    QString m_soundPath;
    //QSound m_sound;

};

#endif // CARD_H
