#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Card.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusBar()->showMessage(tr("All Questions: 0 Remembered: 0 Not Remembered: 0"));
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

}

void MainWindow::on_newQuestionAdded(QString question, QString answer)
{
    ui->label->setText(answer);
    ui->label_2->setText(question);
}
void MainWindow::setDefaultImage()
{
    QPixmap img(":/images/default_image.jpg");
    QRect rect = ui->verticalLayout_4->geometry();
    ui->imageLabel->setPixmap(img.scaled(rect.height(), rect.height()));
}
