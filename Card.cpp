#include "Card.h"

Card::Card(QString q, QString a/*, QImage i, QSound &s*/)
{
    m_question = q;
    m_answer = a;
   // m_image = i;
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
