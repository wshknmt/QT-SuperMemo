#include "NewQuestion.h"
#include "ui_NewQuestion.h"

NewQuestion::NewQuestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewQuestion)
{
    ui->setupUi(this);
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
    close();
}
