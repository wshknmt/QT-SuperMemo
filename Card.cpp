#include "Card.h"
//#include <QPixmap>

Card::Card(QString q, QString a, QPixmap i, QString s, QDate r)
{
    m_question = q;
    m_answer = a;
    m_image = i;
    m_soundPath = s;
    m_repeatDate = r;
}

QString Card::question() const
{
    return m_question;
}

QString Card::answer() const
{
    return m_answer;
}

QPixmap Card::image() const
{
    return m_image;
}

QString Card::soundPath() const
{
    return m_soundPath;
}
QDate Card::repeatDate()
{
    return m_repeatDate;
}
void Card::setRepeatDate(QDate repeatDate)
{
    m_repeatDate = repeatDate;
}
