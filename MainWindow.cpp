#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "NewQuestion.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusBar()->showMessage(tr("All Questions: 0 Remembered: 0 Not Remembered: 0"));
    QPixmap img(":/images/default_image.jpg");
    QRect rect = ui->verticalLayout_4->geometry();
    ui->imageLabel->setPixmap(img.scaled(rect.height(), rect.height()));
   // ui->imageLabel->setPixmap(img.scaled(.height(), rect.height()));
    //ui->imageLabel->setPixmap(img);
    ui->imageLabel->setScaledContents(true);
    //ui->imageLabel->setPixmap(img.scaled(rect.height(), rect.height()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_question_triggered()
{
    NewQuestion *nq = new NewQuestion;
    nq->show();
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}
