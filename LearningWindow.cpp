#include "LearningWindow.h"
#include "ui_LearningWindow.h"
#include "Card.h"
#include <iostream>

#include <unistd.h>
LearningWindow::LearningWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LearningWindow)
{
    course = new Course(this);
    setDefaultValues();
}

LearningWindow::LearningWindow(QList <Course*> &cList, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LearningWindow)
{
    course = new Course(this);
    setDefaultValues();
    coursesList = &cList;
    (*coursesList).append(course);
    courseNumber = (*coursesList).size()-1;
}

LearningWindow::LearningWindow(QList <Course*> &cList, int numberOfSelectedCourse, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LearningWindow)
{
    setDefaultValues();
    course = cList[numberOfSelectedCourse];
    courseNumber = numberOfSelectedCourse;
    coursesList = &cList;
}

void LearningWindow::updateCoursesList()
{
    (*coursesList)[courseNumber] = course;
}

LearningWindow::~LearningWindow()
{
    delete ui;

}

void LearningWindow::on_actionNew_question_triggered()
{
    /*nq = new NewQuestion(this);
    nq->setWindowTitle("Add new question");
    connect(nq, &NewQuestion::newQuestionReady, this, &LearningWindow::on_newQuestionAdded);
    nq->show();*/
    NewQuestion dialog(this);
    if(dialog.exec() )
    {
        //QTextStream(stdout) << "otwarto ekran pytania" << Qt::endl;
        on_newQuestionAdded(dialog.getQuestion(), dialog.getAnswer(), dialog.getImage(), dialog.getSoundPath());
    }
}

void LearningWindow::on_actionExit_triggered()
{
    //QCoreApplication::quit();
    close();
}

void LearningWindow::on_showAnswerButton_clicked()
{
    ui->showAnswerButton_2->setEnabled(false);
    ui->answerTextBrowser_2->setText(card->answer());
    ui->yesButton_2->setEnabled(true);
    ui->noButton_2->setEnabled(true);
    //ui->actionDelete_Question->setEnabled(false);
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
    QRect rect = ui->verticalLayout_7->geometry();
    ui->imageLabel_2->setPixmap(img.scaled(rect.height(), rect.height()));
}

void LearningWindow::setDefaultValues()
{
    ui->setupUi(this);
    ui->showAnswerButton_2->setEnabled(false);
    ui->playButton_2->setEnabled(false);
    ui->stopButton_2->setEnabled(false);
    ui->yesButton_2->setEnabled(false);
    ui->noButton_2->setEnabled(false);
    //ui->actionDelete_Question->setEnabled(false);
    //ui->actionImport->setEnabled(false);
    //ui->actionExport->setEnabled(false);
    connect(this, &LearningWindow::questionAvailable, this, &LearningWindow::on_startLearning);

}

void LearningWindow::setImage(QPixmap image)
{
    QRect rect = ui->verticalLayout_7->geometry();
    ui->imageLabel_2->setPixmap(image.scaled(rect.height(), rect.height()));
}

void LearningWindow::updateProgressBar()
{
    if(course->getCardsCounter() > 0)
    {
        int val = 100 - course->getSizeCardsToRepeat() * 100 / course->getCardsCounter();
        ui->progressBar_2->setValue(val);
    }
    else
        ui->progressBar_2->setValue(0);
}

void LearningWindow::updateStatusLabel()
{
    if(course->getCardsCounter() == course->getSizeCardsRepeated() && course->getCardsCounter() != 0)
    {
        ui->statusLabel_2->setText("Congratulations, you learned all for today :)");
        QPixmap img(":/images/congratulations.png");
        setImage(img);
    }
    else
        ui->statusLabel_2->setText(QString("All Questions: " + QString::number(course->getCardsCounter()) + " Not remembered: " + QString::number(course->getSizeCardsToRepeat()) +
                                         " Remembered: " + QString::number(course->getSizeCardsRepeated())));
}

void LearningWindow::on_startLearning()
{
    card = course->getFirstCardToRepeat();
    ui->showAnswerButton_2->setEnabled(true);
    ui->questionTextBrowser_2->setText(card->question());
   // ui->actionDelete_Question->setEnabled(true);
    if(!card->image().isNull())
        setImage(card->image());
    else
        setDefaultImage();
    if(!card->soundPath().isEmpty())
    {
        ui->playButton_2->setEnabled(true);
    }
}

void LearningWindow::on_yesButton_clicked()
{
    ui->yesButton_2->setEnabled(false);
    ui->noButton_2->setEnabled(false);
    if(card->soundPath().length() != 0)
        sound->stop();
    ui->stopButton_2->setEnabled(false);
    ui->playButton_2->setEnabled(false);
    course->removeFirstCardToRepeat();
    course->addCardRepeated(card);
    setDefaultImage();
    updateProgressBar();
    updateStatusLabel();
    ui->questionTextBrowser_2->clear();
    ui->answerTextBrowser_2->clear();
    if (course->getSizeCardsToRepeat() >= 1)
        emit questionAvailable();
}

void LearningWindow::on_noButton_clicked()
{
    ui->yesButton_2->setEnabled(false);
    ui->noButton_2->setEnabled(false);
    if(card->soundPath().length() != 0)
        sound->stop();
    ui->stopButton_2->setEnabled(false);
    ui->playButton_2->setEnabled(false);
    course->removeFirstCardToRepeat();
    course->addCardToRepeat(card);
    setDefaultImage();
    ui->questionTextBrowser_2->clear();
    ui->answerTextBrowser_2->clear();
    emit questionAvailable();
}

void LearningWindow::on_actionDelete_Question_triggered()
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
        ui->showAnswerButton_2->setEnabled(false);
        ui->playButton_2->setEnabled(false);
        ui->stopButton_2->setEnabled(false);
        setDefaultImage();
        updateProgressBar();
        updateStatusLabel();
        ui->questionTextBrowser_2->clear();
        ui->answerTextBrowser_2->clear();

        if (course->getSizeCardsToRepeat() >= 1)
            emit questionAvailable();
    }
}

void LearningWindow::on_playButton_clicked()
{
    sound = new QSound(card->soundPath());
    sound->setLoops(1000);
    sound->play();
    ui->playButton_2->setEnabled(false);
    ui->stopButton_2->setEnabled(true);
}

void LearningWindow::on_stopButton_clicked()
{
    sound->stop();
    ui->stopButton_2->setEnabled(false);
    ui->playButton_2->setEnabled(true);
}

void LearningWindow::on_pushButton_clicked()
{
    on_actionNew_question_triggered();
}
