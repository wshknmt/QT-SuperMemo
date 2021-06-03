#include <QTextStream>
#include "Card.h"

Card::Card(QString q, QString a, QString i, QString s, QDate r) {
    question_ = q;
    answer_ = a;
    imagePath_ = i;
    soundPath_ = s;
    repeatDate_ = r;
}

QString Card::getQuestion() const {
    return question_;
}

QString Card::getAnswer() const {
    return answer_;
}

QString Card::getImagePath() const {
    return imagePath_;
}

QString Card::getSoundPath() const {
    return soundPath_;
}
QDate Card::getRepeatDate() {
    return repeatDate_;
}
void Card::setRepeatDate(QDate repeatDate) {
    repeatDate_ = repeatDate;
}

void Card::printCard() {
   // QTextStream(stdout) <<" Question: "<< question_ <<" Answer: "<< answer_<<" Repeat_date: "<< repeatDate_.toString(Qt::RFC2822Date) << Qt::endl;
}
