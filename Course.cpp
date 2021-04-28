#include "Course.h"

Course::Course(QObject *parent) : QObject(parent)
{
    cardsCounter = 0;
}

void Course::addCardToRepeat(Card* card)
{
    cardsToRepeat.append(card);
    //cardsCounter++;
    //if (cardsToRepeat.length() == 1)
       // emit
        //return;
}

void Course::addCardRepeated(Card* card)
{
    cardsRepeated.append(card);
    //cardsCounter++;
    //if (cardsToRepeat.length() == 1)
       // emit
        //return;
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

void Course::incrementCardsCounter()
{
    cardsCounter++;
}
