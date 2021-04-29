#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Card.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    course = new Course(this);
    statusBar()->showMessage(tr("All Questions: 0 Remembered: 0 Not Remembered: 0"));
    ui->showAnswerButton->setEnabled(false);
    ui->playButton->setEnabled(false);
    ui->yesButton->setEnabled(false);
    ui->noButton->setEnabled(false);
    ui->progressSlider->setEnabled(false);
    ui->actionDelete_Question->setEnabled(false);
    connect(this, &MainWindow::questionAvailable, this, &MainWindow::on_startLearning);
   // QPixmap img(":/images/default_image.jpg");
   // QRect rect = ui->verticalLayout_4->geometry();
    //ui->imageLabel->setPixmap(img.scaled(rect.height(), rect.height()));
   // ui->imageLabel->setPixmap(img.scaled(.height(), rect.height()));
  //  ui->imageLabel->setPixmap(img);
  //  ui->imageLabel->setScaledContents(true);
    //ui->imageLabel->setPixmap(img.scaled(rect.height(), rect.height()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_question_triggered()
{
    //NewQuestion *nq = new NewQuestion();
    //nq->show();
    nq = new NewQuestion(this);
    connect(nq, &NewQuestion::newQuestionReady, this, &MainWindow::on_newQuestionAdded);
    nq->show();
    /*QString x = nq->getAnswer();
    QString y = nq->getQuestion();
    std::cout<<x.toStdString()<<" "<<y.toStdString()<<std::endl;
    ui->label->setText(x);
    ui->label_2->setText(y);
    //nq->visi*/
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

void MainWindow::on_newQuestionAdded(QString question, QString answer)
{
    //Card
    newCard = new Card(question, answer);
    //course->cardsToRepeat

    course->addCardToRepeat(newCard);
    course->incrementCardsCounter();
    updateProgressBar();
    if (course->getSizeCardsToRepeat() == 1)
        emit questionAvailable();
   // ui->label->setText(answer);
    //ui->label_2->setText(question);

}
void MainWindow::setDefaultImage()
{
    QPixmap img(":/images/default_image.jpg");
    QRect rect = ui->verticalLayout_4->geometry();
    ui->imageLabel->setPixmap(img.scaled(rect.height(), rect.height()));
}

void MainWindow::updateProgressBar()
{
    int val = 100 - course->getSizeCardsToRepeat() * 100 / course->getCardsCounter();
    ui->progressBar->setValue(val);
}

void MainWindow::on_startLearning()
{
    card = course->getFirstCardToRepeat();
    ui->showAnswerButton->setEnabled(true);
    ui->questionTextBrowser->setText(card->question());
    ui->actionDelete_Question->setEnabled(true);

}

void MainWindow::on_yesButton_clicked()
{
    ui->yesButton->setEnabled(false);
    ui->noButton->setEnabled(false);
    course->removeFirstCardToRepeat();
    course->addCardRepeated(card);
    updateProgressBar();
    ui->questionTextBrowser->clear();
    ui->answerTextBrowser->clear();
    if (course->getSizeCardsToRepeat() >= 1)
        emit questionAvailable();
}

void MainWindow::on_noButton_clicked()
{
    ui->yesButton->setEnabled(false);
    ui->noButton->setEnabled(false);
    course->removeFirstCardToRepeat();
    course->addCardToRepeat(card);
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
        course->removeFirstCardToRepeat();
        course->decrementCardsCounter();
        ui->showAnswerButton->setEnabled(false);
        updateProgressBar();
        ui->questionTextBrowser->clear();
        ui->answerTextBrowser->clear();
        if (course->getSizeCardsToRepeat() >= 1)
            emit questionAvailable();
    }


}
