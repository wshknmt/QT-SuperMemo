#include <QTextStream>
#include "Course.h"

Course::Course(QString n, QObject *parent) : QObject(parent) {
    cardsCounter_ = 0;
    name_ = n;
    progress_ = 0;
}

Course::Course(QObject *parent) : QObject(parent) {
    cardsCounter_ = 0;
    name_ = "default_course_name";
    progress_ = 0;
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

int Course::getCardsCounter() {
    return cardsCounter_;
}

Card* Course::getFirstCardToRepeat() {
    return cardsToRepeat_[0];
}

Card* Course::getCardToRepeat(int number) {
    return cardsToRepeat_[number];
}
Card* Course::getCardRepeated(int number) {
    return cardsRepeated_[number];
}

int Course::getSizeCardsToRepeat() {
    return cardsToRepeat_.length();
}

int Course::getSizeCardsRepeated() {
    return cardsRepeated_.length();
}

void Course::incrementCardsCounter() {
    cardsCounter_++;
}

void Course::decrementCardsCounter() {
    cardsCounter_--;
}
QString Course::getName() {
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

int Course::getProgress() {
    return progress_;
}

void Course::printCourse() {
    QTextStream(stdout) <<"CourseName:  "<< name_ <<" cards counter "<< cardsCounter_<< Qt::endl;
    QTextStream(stdout) <<"Cards To Repeat:  "<< Qt::endl;
    for(int i=0; i < cardsToRepeat_.size(); i++) {
        QTextStream(stdout) <<"    "<< i+1 <<". ";
        cardsToRepeat_[i]->printCard();
    }
    QTextStream(stdout) <<"Cards Repeated:  "<< Qt::endl;
    for(int i=0; i < cardsRepeated_.size(); i++) {
        QTextStream(stdout) <<"    "<< i+1 <<". ";
        cardsRepeated_[i]->printCard();
    }
}

bool Course::isEqualToCurrentDate(QDate date) {
    QDate current = QDate::currentDate();
    if(current.day() == date.day() && current.month() == date.month() && current.year() == date.year())
        return true;
    return false;
}

void Course::checkCards() {
    for(int i = 0; i < cardsRepeated_.size(); i++) {
        if(cardsRepeated_[i]->getRepeatDate() < QDate::currentDate() || isEqualToCurrentDate(cardsRepeated_[i]->getRepeatDate())) {
            cardsToRepeat_.append(cardsRepeated_[i]);
            cardsRepeated_.removeAt(i);
            i--;
        }
    }
}

void Course::simulateTime(qint64 days) {
    for(int i=0; i < cardsRepeated_.size(); i++)
        cardsRepeated_[i]->setRepeatDate(cardsRepeated_[i]->getRepeatDate().addDays(days));
}

void Course::reviewRequest() {
    for(int i = 0; i < cardsRepeated_.size(); i++)
        cardsToRepeat_.append(cardsRepeated_[i]);
    cardsRepeated_.clear();
}
