/*
 * File name: Course.cc
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class representing one course.
 */

#include <QTextStream>

#include "Course.h"

Course::Course(QString n) : name_(n), progress_(0), cardsCounter_(0) {}

Course::Course() : name_("default_course_name"), progress_(0), cardsCounter_(0) {}

Course::~Course() {
    for (Card* cPtr : cardsToRepeat_)
        delete cPtr;
    for (Card* cPtr : cardsRepeated_)
        delete cPtr;
}

void Course::addCardToRepeat(Card* card) {
    cardsToRepeat_.append(card);
}

void Course::addCardRepeated(Card* card) {
    cardsRepeated_.append(card);
}

void Course::removeFirstCardToRepeat() {
    cardsToRepeat_.pop_front();
}

void Course::removeFirstCardRepeated() {
    cardsRepeated_.pop_front();
}

int Course::getCardsCounter() const {
    return cardsCounter_;
}

Card* Course::getFirstCardToRepeat() const {
    return cardsToRepeat_[0];
}

Card* Course::getCardToRepeat(int number) const {
    return cardsToRepeat_[number];
}

Card* Course::getCardRepeated(int number) const {
    return cardsRepeated_[number];
}

int Course::getSizeCardsToRepeat() const {
    return cardsToRepeat_.length();
}

int Course::getSizeCardsRepeated() const {
    return cardsRepeated_.length();
}

void Course::incrementCardsCounter() {
    ++cardsCounter_;
}

void Course::decrementCardsCounter() {
    --cardsCounter_;
}
QString Course::getName() const {
    return name_;
}

void Course::countProgress() {
    if(getCardsCounter() > 0 && getCardsCounter() == getSizeCardsRepeated())
        progress_ = 100;
    else if (getCardsCounter() > 0)
        progress_ = 100 - getSizeCardsToRepeat() * 100 / getCardsCounter();
    else
        progress_ = 0;
}

int Course::getProgress() const {
    return progress_;
}

bool Course::isEqualToCurrentDate(QDate date) const {
    QDate current = QDate::currentDate();
    if(current.day() == date.day() && current.month() == date.month() && current.year() == date.year())
        return true;
    return false;
}

void Course::checkCards() {
    for(int i = 0; i < cardsRepeated_.size(); ++i) {
        if(cardsRepeated_[i]->getRepeatDate() < QDate::currentDate() || isEqualToCurrentDate(cardsRepeated_[i]->getRepeatDate())) {
            cardsToRepeat_.append(cardsRepeated_[i]);
            cardsRepeated_.removeAt(i);
            i--;
        }
    }
}

void Course::simulateTime(qint64 days) {
    for(int i=0; i < cardsRepeated_.size(); ++i)
        cardsRepeated_[i]->setRepeatDate(cardsRepeated_[i]->getRepeatDate().addDays(days));
}

void Course::reviewRequest() {
    for(int i = 0; i < cardsRepeated_.size(); ++i)
        cardsToRepeat_.append(cardsRepeated_[i]);
    cardsRepeated_.clear();
}
