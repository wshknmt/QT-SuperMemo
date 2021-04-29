#include "Card.h"
//#include <QPixmap>

Card::Card(QString q, QString a, QPixmap i /* QSound &s*/)
{
    m_question = q;
    m_answer = a;
    m_image = i;
   // m_sound = s;
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
