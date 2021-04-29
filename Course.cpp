#include "Course.h"

Course::Course(QObject *parent) : QObject(parent)
{
    cardsCounter = 0;
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
