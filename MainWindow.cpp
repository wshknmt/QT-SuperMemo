#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Card.h"
#include <iostream>

#include <unistd.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    course = new Course(this);
    ui->showAnswerButton->setEnabled(false);
    ui->playButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->yesButton->setEnabled(false);
    ui->noButton->setEnabled(false);
    ui->actionDelete_Question->setEnabled(false);
    ui->actionImport->setEnabled(false);
    ui->actionExport->setEnabled(false);
    connect(this, &MainWindow::questionAvailable, this, &MainWindow::on_startLearning);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_question_triggered()
{
    nq = new NewQuestion(this);
    connect(nq, &NewQuestion::newQuestionReady, this, &MainWindow::on_newQuestionAdded);
    nq->show();
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_showAnswerButton_clicked()
{
    ui->showAnswerButton->setEnabled(false);
    ui->answerTextBrowser->setText(card->answer());
    ui->yesButton->setEnabled(true);
    ui->noButton->setEnabled(true);
    ui->actionDelete_Question->setEnabled(false);
}

void MainWindow::on_newQuestionAdded(QString question, QString answer, QPixmap image, QString soundPath)
{
    newCard = new Card(question, answer, image, soundPath);
    course->addCardToRepeat(newCard);
    course->incrementCardsCounter();
    updateProgressBar();
    updateStatusLabel();
    if (course->getSizeCardsToRepeat() == 1)
        emit questionAvailable();
}
void MainWindow::setDefaultImage()
{
    QPixmap img(":/images/default_image.jpg");
    QRect rect = ui->verticalLayout_4->geometry();
    ui->imageLabel->setPixmap(img.scaled(rect.height(), rect.height()));
}

void MainWindow::setImage(QPixmap image)
{
    QRect rect = ui->verticalLayout_4->geometry();
    ui->imageLabel->setPixmap(image.scaled(rect.height(), rect.height()));
}

void MainWindow::updateProgressBar()
{
    if(course->getCardsCounter() > 0)
    {
        int val = 100 - course->getSizeCardsToRepeat() * 100 / course->getCardsCounter();
        ui->progressBar->setValue(val);
    }
    else
        ui->progressBar->setValue(0);
}

void MainWindow::updateStatusLabel()
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

void MainWindow::on_startLearning()
{
    card = course->getFirstCardToRepeat();
    ui->showAnswerButton->setEnabled(true);
    ui->questionTextBrowser->setText(card->question());
    ui->actionDelete_Question->setEnabled(true);
    if(!card->image().isNull())
        setImage(card->image());
    else
        setDefaultImage();
    if(!card->soundPath().isEmpty())
    {
        ui->playButton->setEnabled(true);
    }
}

void MainWindow::on_yesButton_clicked()
{
    ui->yesButton->setEnabled(false);
    ui->noButton->setEnabled(false);
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

void MainWindow::on_noButton_clicked()
{
    ui->yesButton->setEnabled(false);
    ui->noButton->setEnabled(false);
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

void MainWindow::on_actionDelete_Question_triggered()
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

void MainWindow::on_playButton_clicked()
{
    sound = new QSound(card->soundPath());
    sound->setLoops(1000);
    sound->play();
    ui->playButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}

void MainWindow::on_stopButton_clicked()
{
    sound->stop();
    ui->stopButton->setEnabled(false);
    ui->playButton->setEnabled(true);
}
