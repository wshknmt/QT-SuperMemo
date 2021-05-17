#include "LearningWindow.h"
#include "ui_LearningWindow.h"
#include "Card.h"
#include <iostream>

#include <unistd.h>
LearningWindow::LearningWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LearningWindow)
{
    course = new Course("default_course_name", this);
    QTextStream(stdout) << "0 learn win" << Qt::endl;
    setDefaultValues();
}

LearningWindow::LearningWindow(QList <Course*> &cList, QString courseName, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LearningWindow)
{
    if(courseName.isEmpty())
        course = new Course();
    else
        course = new Course(courseName);
    setDefaultValues();
    coursesList = &cList;
    (cList).append(course);
    courseNumber = cList.size()-1;
}

LearningWindow::LearningWindow(QList <Course*> &cList, int numberOfSelectedCourse, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LearningWindow)
{
    setDefaultValues();
    course = cList[numberOfSelectedCourse];
    courseNumber = numberOfSelectedCourse;
    coursesList = &cList;
    course->checkCards();
    updateProgressBar();
    updateStatusLabel();
    if (course->getSizeCardsToRepeat() >= 1)
    {
        emit questionAvailable();
    }
}

void LearningWindow::updateCoursesList()
{
    (*coursesList)[courseNumber] = course;
}

LearningWindow::~LearningWindow()
{
    delete ui;
}

void LearningWindow::on_showAnswerButton_clicked()
{
    ui->showAnswerButton->setEnabled(false);
    ui->answerTextBrowser->setText(card->answer());
    ui->yesButton->setEnabled(true);
    ui->noButton->setEnabled(true);
    ui->almostButton->setEnabled(true);
    ui->deleteButton->setEnabled(false);
}

void LearningWindow::on_newQuestionAdded(QString question, QString answer, QPixmap image, QString soundPath)
{
    newCard = new Card(question, answer, image, soundPath, QDate::currentDate());
    course->addCardToRepeat(newCard);
    course->incrementCardsCounter();
    updateProgressBar();
    updateStatusLabel();
    if (course->getSizeCardsToRepeat() == 1)
        emit questionAvailable();
}
void LearningWindow::setDefaultImage()
{
    QPixmap img(":/images/default_image.jpg");
    QRect rect = ui->verticalLayout_4->geometry();
    ui->imageLabel->setPixmap(img.scaled(rect.height(), rect.height()));
}

void LearningWindow::setDefaultValues()
{
    ui->setupUi(this);
    ui->showAnswerButton->setEnabled(false);
    ui->playButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->yesButton->setEnabled(false);
    ui->noButton->setEnabled(false);
    ui->almostButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    connect(this, &LearningWindow::questionAvailable, this, &LearningWindow::on_startLearning);
    checkImage();
    QPixmap img1(":/images/Icons/smile.png");
    QPixmap img2(":/images/Icons/neutral.png");
    QPixmap img3(":/images/Icons/sad.png");
    ui->yesButton->setIcon(img1);
    ui->almostButton->setIcon(img2);
    ui->noButton->setIcon(img3);
    QSize iconSize(ui->noButton->height(),ui->noButton->height());
    ui->yesButton->setIconSize(iconSize);
    ui->almostButton->setIconSize(iconSize);
    ui->noButton->setIconSize(iconSize);


}

void LearningWindow::setImage(QPixmap image)
{
    QRect rect = ui->verticalLayout_4->geometry();
    ui->imageLabel->setPixmap(image.scaled(rect.height(), rect.height()));
}

void LearningWindow::updateProgressBar()
{
    if(course->getCardsCounter() > 0 && course->getCardsCounter() == course->getSizeCardsRepeated())
    {
         ui->progressBar->setValue(100);
    }
    else if (course->getCardsCounter() > 0)
    {
        int val = 100 - course->getSizeCardsToRepeat() * 100 / course->getCardsCounter();
        ui->progressBar->setValue(val);
    }
    else
        ui->progressBar->setValue(0);
}

void LearningWindow::updateStatusLabel()
{
    if(course->getCardsCounter() == course->getSizeCardsRepeated() && course->getCardsCounter() != 0)
    {
        ui->statusLabel->setText("Congratulations, you learned all for today :)");
        QPixmap img(":/images/congratulations.png");
        setImage(img);
    }
    else
        ui->statusLabel->setText(QString("All Questions: " + QString::number(course->getCardsCounter()) + " Not remembered: " + QString::number(course->getSizeCardsToRepeat()) +
                                         " Remembered: " + QString::number(course->getSizeCardsRepeated())));
}

void LearningWindow::on_startLearning()
{
    card = course->getFirstCardToRepeat();
    ui->showAnswerButton->setEnabled(true);
    ui->questionTextBrowser->setText(card->question());
    ui->deleteButton->setEnabled(true);
    if(!card->image().isNull())
        setImage(card->image());
    else
        setDefaultImage();
    if(!card->soundPath().isEmpty())
    {
        ui->playButton->setEnabled(true);
    }
}

void LearningWindow::on_yesButton_clicked()
{
    if(card->repeatDate() <= QDate::currentDate())
        card->setRepeatDate(QDate::currentDate().addDays(5));

    ui->yesButton->setEnabled(false);
    ui->noButton->setEnabled(false);
    ui->almostButton->setEnabled(false);
    if(card->soundPath().length() != 0)
        sound->stop();
    ui->stopButton->setEnabled(false);
    ui->playButton->setEnabled(false);
    course->removeFirstCardToRepeat();
    course->addCardRepeated(card);
    setDefaultImage();
    updateProgressBar();
    updateStatusLabel();
    ui->questionTextBrowser->clear();
    ui->answerTextBrowser->clear();
    if (course->getSizeCardsToRepeat() >= 1)
        emit questionAvailable();
}

void LearningWindow::on_noButton_clicked()
{
    if(card->repeatDate() <= QDate::currentDate())
        card->setRepeatDate(QDate::currentDate().addDays(2));
    ui->yesButton->setEnabled(false);
    ui->noButton->setEnabled(false);
    ui->almostButton->setEnabled(false);
    if(card->soundPath().length() != 0)
        sound->stop();
    ui->stopButton->setEnabled(false);
    ui->playButton->setEnabled(false);
    course->removeFirstCardToRepeat();
    course->addCardToRepeat(card);
    setDefaultImage();
    ui->questionTextBrowser->clear();
    ui->answerTextBrowser->clear();
    emit questionAvailable();
}

void LearningWindow::on_almostButton_clicked()
{
    if(card->repeatDate() <= QDate::currentDate())
        card->setRepeatDate(QDate::currentDate().addDays(3));

    ui->yesButton->setEnabled(false);
    ui->noButton->setEnabled(false);
    ui->almostButton->setEnabled(false);
    if(card->soundPath().length() != 0)
        sound->stop();
    ui->stopButton->setEnabled(false);
    ui->playButton->setEnabled(false);
    course->removeFirstCardToRepeat();
    course->addCardRepeated(card);
    setDefaultImage();
    updateProgressBar();
    updateStatusLabel();
    ui->questionTextBrowser->clear();
    ui->answerTextBrowser->clear();
    if (course->getSizeCardsToRepeat() >= 1)
        emit questionAvailable();
}

void LearningWindow::on_playButton_clicked()
{
    sound = new QSound(card->soundPath());
    sound->setLoops(1000);
    sound->play();
    ui->playButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}

void LearningWindow::on_stopButton_clicked()
{
    sound->stop();
    ui->stopButton->setEnabled(false);
    ui->playButton->setEnabled(true);
}

void LearningWindow::on_newQuestionButton_clicked()
{
    NewQuestion dialog(this);
    if(dialog.exec() )
    {
        on_newQuestionAdded(dialog.getQuestion(), dialog.getAnswer(), dialog.getImage(), dialog.getSoundPath());
    }
}

void LearningWindow::on_deleteButton_clicked()
{
    QMessageBox msg;
    msg.setText("Are you sure you want to delete this question?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    int ret = msg.exec();
    if (ret == QMessageBox::Yes)
    {
        if(card->soundPath().length() != 0)
            sound->stop();
        course->removeFirstCardToRepeat();
        course->decrementCardsCounter();
        ui->showAnswerButton->setEnabled(false);
        ui->playButton->setEnabled(false);
        ui->stopButton->setEnabled(false);
        setDefaultImage();
        updateProgressBar();
        updateStatusLabel();
        ui->questionTextBrowser->clear();
        ui->answerTextBrowser->clear();
        if (course->getSizeCardsToRepeat() >= 1)
            emit questionAvailable();
    }
}

void LearningWindow::on_endButton_clicked()
{
    accept();
}
void LearningWindow::checkImage()
{
//    if(course->getSizeCardsToRepeat() >= 1)
//    {
//        if(!course->getFirstCardToRepeat()->image().isNull())
//        {
//            setImage(course->getFirstCardToRepeat()->image());
//            return;
//        }
//    }
//    setDefaultImage();
}

bool LearningWindow::isEqualToCurrentDate(QDate date)
{
    QDate current = QDate::currentDate();
    if(current.day() == date.day() && current.month() == date.month() && current.year() == date.year())
        return true;
    return false;
}


