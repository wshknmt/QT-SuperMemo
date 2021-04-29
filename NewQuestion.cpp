#include "NewQuestion.h"
#include "ui_NewQuestion.h"

NewQuestion::NewQuestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewQuestion)
{
    ui->setupUi(this);
    QPixmap img1(":/images/Icons/photo.png");
    QPixmap img2(":/images/Icons/sound.png");
    ui->imageAddButton->setIcon(img1);
    ui->soundAddButton->setIcon(img2);
    ui->okButton->setEnabled(false);
    answer = "";
    question = "";
}

NewQuestion::~NewQuestion()
{
    delete ui;
}

QString NewQuestion::getQuestion()
{
    return question;
}

QString NewQuestion::getAnswer()
{
    return answer;
}

void NewQuestion::on_okButton_clicked()
{
    answer = ui->textEdit->toPlainText();
    question = ui->textEdit_2->toPlainText();
    emit newQuestionReady(question, answer);
    close();
}

void NewQuestion::on_cancelButton_clicked()
{
    QMessageBox msg;
    msg.setText("Are you sure you want to exit?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    int ret = msg.exec();
    if (ret == QMessageBox::Yes)
        close();
}

void NewQuestion::on_textEdit_2_textChanged()
{
    if(ui->textEdit_2->toPlainText().length() >= 1 && ui->textEdit->toPlainText().length() >= 1)
        ui->okButton->setEnabled(true);
    else
        ui->okButton->setEnabled(false);
}

void NewQuestion::on_textEdit_textChanged()
{
    if(ui->textEdit_2->toPlainText().length() >= 1 && ui->textEdit->toPlainText().length() >= 1)
        ui->okButton->setEnabled(true);
    else
        ui->okButton->setEnabled(false);
}
