#include "Course.h"
#include <QTextStream>

Course::Course(QString n, QObject *parent) : QObject(parent)
{
    cardsCounter = 0;
    name = n;
}

Course::Course(QObject *parent) : QObject(parent)
{
    cardsCounter = 0;
    name = "default_course_name";
}

void Course::addCardToRepeat(Card* card)
{
    cardsToRepeat.append(card);
}

void Course::addCardRepeated(Card* card)
{
    cardsRepeated.append(card);
}

void Course::removeFirstCardToRepeat()
{
    cardsToRepeat.pop_front();
}

void Course::removeFirstCardRepeated()
{
    cardsRepeated.pop_front();
}

int Course::getCardsCounter()
{
    return cardsCounter;
}

Card* Course::getFirstCardToRepeat()
{
    return cardsToRepeat[0];
}

int Course::getSizeCardsToRepeat()
{
    return cardsToRepeat.length();
}

int Course::getSizeCardsRepeated()
{
    return cardsRepeated.length();
}

void Course::incrementCardsCounter()
{
    cardsCounter++;
}

void Course::decrementCardsCounter()
{
    cardsCounter--;
}
QString Course::getName()
{
    return name;
}

void Course::printCourse()
{
    QTextStream(stdout) <<"CourseName:  "<< name <<" cards counter "<< cardsCounter<< Qt::endl;
    QTextStream(stdout) <<"Cards To Repeat:  "<< Qt::endl;
    for(int i=0; i < cardsToRepeat.size(); i++)
    {
        QTextStream(stdout) <<"    "<< i+1 <<". ";
        cardsToRepeat[i]->printCard();
    }
    //QTextStream(stdout)<<" "<<Qt::endl;
    QTextStream(stdout) <<"Cards Repeated:  "<< Qt::endl;
    for(int i=0; i < cardsRepeated.size(); i++)
    {
        QTextStream(stdout) <<"    "<< i+1 <<". ";
        cardsRepeated[i]->printCard();
    }
}

bool Course::isEqualToCurrentDate(QDate date)
{
    QDate current = QDate::currentDate();
    if(current.day() == date.day() && current.month() == date.month() && current.year() == date.year())
        return true;
    return false;
}

void Course::checkCards()
{
    for(int i=0; i < cardsRepeated.size(); i++)
    {
        //if(isEqualToCurrentDate(cardsRepeated[i]->repeatDate()))
        if(cardsRepeated[i]->repeatDate() < QDate::currentDate())
        {
            cardsToRepeat.append(cardsRepeated[i]);
            cardsRepeated.removeAt(i);
        }
    }
}

void Course::simulateTime(qint64 days)
{
    for(int i=0; i < cardsRepeated.size(); i++)
    {
        cardsRepeated[i]->setRepeatDate(cardsRepeated[i]->repeatDate().addDays(days));

        QTextStream(stdout)<<"tu: "<<cardsRepeated[i]->repeatDate().toString(Qt::RFC2822Date)<<Qt::endl;
    }
}
