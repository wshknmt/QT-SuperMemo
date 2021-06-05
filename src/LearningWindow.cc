/*
 * File name: LearningWindow.cc
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class implementing functions for questions answering window.
 */

#include "LearningWindow.h"
#include "ui_LearningWindow.h"
#include "Card.h"
#include "CoursesManager.h"
#include "Settings.h"

LearningWindow::LearningWindow(CoursesManager &cManager, UserStats &uStats, QString courseName, QWidget *parent)
    : QDialog(parent), ui_(new Ui::LearningWindow), coursesManager_(&cManager), userStats_(&uStats)
{
    if(courseName.isEmpty())
        course_ = coursesManager_->createCourse();
    else
        course_ = coursesManager_->createCourse(courseName);
    setDefaultValues();
}

LearningWindow::LearningWindow(CoursesManager &cManager, UserStats &uStats, int numberOfSelectedCourse, QWidget *parent)
    : QDialog(parent), ui_(new Ui::LearningWindow), coursesManager_(&cManager), userStats_(&uStats)
{
    setDefaultValues();
    course_ = coursesManager_->getCourse(numberOfSelectedCourse);
    course_->checkCards();
    updateProgressBar();
    updateStatusLabel();
    if (course_->getSizeCardsToRepeat() >= 1)
        emit questionAvailable();
}

LearningWindow::~LearningWindow() {
    delete ui_;
}

void LearningWindow::on_showAnswerButton_clicked() {
    ui_->showAnswerButton->setEnabled(false);
    ui_->answerTextBrowser->setText(card_->getAnswer());
    ui_->yesButton->setEnabled(true);
    ui_->noButton->setEnabled(true);
    ui_->almostButton->setEnabled(true);
    ui_->deleteButton->setEnabled(false);
}

void LearningWindow::on_newQuestionAdded(QString question, QString answer, QString imagePath, QString soundPath) {
    Card *newCard = new Card(question, answer, imagePath, soundPath, QDate::currentDate());
    course_->addCardToRepeat(newCard);
    course_->incrementCardsCounter();
    updateProgressBar();
    updateStatusLabel();
    if (course_->getSizeCardsToRepeat() == 1)
        emit questionAvailable();
}
void LearningWindow::setDefaultImage() {
    QPixmap img(":/images/default_image.jpg");
    QRect rect = ui_->verticalLayout_4->geometry();
    ui_->imageLabel->setPixmap(img.scaled(rect.height(), rect.height()));
}

void LearningWindow::setDefaultValues() {
    ui_->setupUi(this);
    ui_->showAnswerButton->setEnabled(false);
    ui_->playButton->setEnabled(false);
    ui_->stopButton->setEnabled(false);
    ui_->yesButton->setEnabled(false);
    ui_->noButton->setEnabled(false);
    ui_->almostButton->setEnabled(false);
    ui_->deleteButton->setEnabled(false);
    connect(this, &LearningWindow::questionAvailable, this, &LearningWindow::on_startLearning);
    QPixmap img1(":/images/Icons/smile.png");
    QPixmap img2(":/images/Icons/neutral.png");
    QPixmap img3(":/images/Icons/sad.png");
    ui_->yesButton->setIcon(img1);
    ui_->almostButton->setIcon(img2);
    ui_->noButton->setIcon(img3);
    QSize iconSize(ui_->noButton->height(),ui_->noButton->height());
    ui_->yesButton->setIconSize(iconSize);
    ui_->almostButton->setIconSize(iconSize);
    ui_->noButton->setIconSize(iconSize);
    ui_->answerTextBrowser->setFont(Settings::getInstance()->getFont());
    ui_->questionTextBrowser->setFont(Settings::getInstance()->getFont());
}

void LearningWindow::setImage(QPixmap image) {
    QRect rect = ui_->verticalLayout_4->geometry();
    ui_->imageLabel->setPixmap(image.scaled(rect.height(), rect.height()));
}

void LearningWindow::updateProgressBar() {
    course_->countProgress();
    ui_->progressBar->setValue(course_->getProgress());
}

void LearningWindow::updateStatusLabel() {
    if(course_->getCardsCounter() == course_->getSizeCardsRepeated() && course_->getCardsCounter() != 0) {
        ui_->statusLabel->setText("Gratulacje, ukończyłeś cały kurs :)");
        QPixmap img(":/images/congratulations.png");
        setImage(img);
    }
    else
        ui_->statusLabel->setText(QString("Wszystkie pytania: " + QString::number(course_->getCardsCounter()) + " Jeszcze nie zapamiętane: " + QString::number(course_->getSizeCardsToRepeat()) +
                                         " Już zapamiętane: " + QString::number(course_->getSizeCardsRepeated())));
}

void LearningWindow::on_startLearning() {
    card_ = course_->getFirstCardToRepeat();
    ui_->showAnswerButton->setEnabled(true);
    ui_->questionTextBrowser->setText(card_->getQuestion());
    ui_->deleteButton->setEnabled(true);
    if(!card_->getImagePath().isEmpty()) {
        QPixmap image;
        image.load(card_->getImagePath());
        setImage(image);
    }
    else
        setDefaultImage();
    if(!card_->getSoundPath().isEmpty())
        ui_->playButton->setEnabled(true);
}

void LearningWindow::on_yesButton_clicked() {
    if(card_->getRepeatDate() <= QDate::currentDate())
        card_->setRepeatDate(QDate::currentDate().addDays(5));
    Stat stat = std::make_pair(QDate::currentDate(), AnswerType::GOOD);
    userStats_->addStat(stat);
    course_->removeFirstCardToRepeat();
    course_->addCardRepeated(card_);
    answerRated();
}

void LearningWindow::on_noButton_clicked() {
    if(card_->getRepeatDate() <= QDate::currentDate())
        card_->setRepeatDate(QDate::currentDate().addDays(2));
    Stat stat = std::make_pair(QDate::currentDate(), AnswerType::WRONG);
    userStats_->addStat(stat);
    course_->removeFirstCardToRepeat();
    course_->addCardToRepeat(card_);
    answerRated();
}

void LearningWindow::on_almostButton_clicked() {
    if(card_->getRepeatDate() <= QDate::currentDate())
        card_->setRepeatDate(QDate::currentDate().addDays(3));
    Stat stat = std::make_pair(QDate::currentDate(), AnswerType::MIXED);
    userStats_->addStat(stat);
    course_->removeFirstCardToRepeat();
    course_->addCardRepeated(card_);
    answerRated();
}

void LearningWindow::answerRated() {
    ui_->yesButton->setEnabled(false);
    ui_->noButton->setEnabled(false);
    ui_->almostButton->setEnabled(false);
    if(card_->getSoundPath().length() != 0 && ui_->playButton->isEnabled() == false)
        sound_->stop();
    ui_->stopButton->setEnabled(false);
    ui_->playButton->setEnabled(false);
    setDefaultImage();
    updateProgressBar();
    updateStatusLabel();
    ui_->questionTextBrowser->clear();
    ui_->answerTextBrowser->clear();
    if (course_->getSizeCardsToRepeat() >= 1)
        emit questionAvailable();
}

void LearningWindow::on_playButton_clicked() {
    sound_ = new QSound(card_->getSoundPath());
    sound_->setLoops(1000);
    sound_->play();
    ui_->playButton->setEnabled(false);
    ui_->stopButton->setEnabled(true);
}

void LearningWindow::on_stopButton_clicked() {
    sound_->stop();
    ui_->stopButton->setEnabled(false);
    delete sound_;
    ui_->playButton->setEnabled(true);
}

void LearningWindow::on_newQuestionButton_clicked() {
    NewQuestion dialog(this);
    dialog.setWindowTitle("Dodaj nowe pytanie");
    if(dialog.exec() ) {
        on_newQuestionAdded(dialog.getQuestion(), dialog.getAnswer(), dialog.getImagePath(), dialog.getSoundPath());
    }
}

void LearningWindow::on_deleteButton_clicked() {
    QMessageBox msg;
    msg.setText("Jesteś pewny że chcesz usunąć to pytanie?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    int ret = msg.exec();
    if (ret == QMessageBox::Yes) {
        if(card_->getSoundPath().length() != 0 && ui_->playButton->isEnabled() == false)
            sound_->stop();
        course_->removeFirstCardToRepeat();
        course_->decrementCardsCounter();
        ui_->showAnswerButton->setEnabled(false);
        ui_->playButton->setEnabled(false);
        ui_->stopButton->setEnabled(false);
        setDefaultImage();
        updateProgressBar();
        updateStatusLabel();
        ui_->questionTextBrowser->clear();
        ui_->answerTextBrowser->clear();
        if (course_->getSizeCardsToRepeat() >= 1)
            emit questionAvailable();
        else {
            ui_->deleteButton->setEnabled(false);
        }
    }
}

void LearningWindow::on_endButton_clicked() {
    if(card_->getSoundPath().length() != 0 && ui_->playButton->isEnabled() == false)
        sound_->stop();
    accept();
}

bool LearningWindow::isEqualToCurrentDate(QDate date) const {
    QDate current = QDate::currentDate();
    if(current.day() == date.day() && current.month() == date.month() && current.year() == date.year())
        return true;
    return false;
}

int LearningWindow::getProgressBarValue() const {
    return ui_->progressBar->value();
}


