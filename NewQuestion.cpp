#include <QFileDialog>
#include "NewQuestion.h"
#include "ui_NewQuestion.h"
#include <QStandardPaths>


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
    soundPath.clear();
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
QPixmap NewQuestion::getImage()
{
    return image;
}
QString NewQuestion::getImagePath()
{
    return " ";
}
QString NewQuestion::getSoundPath()
{
    return soundPath;
}

void NewQuestion::on_okButton_clicked()
{
    answer = ui->textEdit->toPlainText();
    question = ui->textEdit_2->toPlainText();
    //emit newQuestionReady(question, answer, image, soundPath);
    accept();
}

void NewQuestion::on_cancelButton_clicked()
{
    QMessageBox msg;
    msg.setText("Are you sure you want to exit?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    int ret = msg.exec();
    if (ret == QMessageBox::Yes)
        reject();
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

void NewQuestion::on_imageAddButton_clicked()
{
    ui->imageAddButton->setEnabled(false);
    ui->imageAddButton->setText("Image added");
    imagePath = QFileDialog::getOpenFileName(this,
        "Open image", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("JPG file (*.jpg *.jpeg);; PNG fils (*.png);; BMP file (*.bmp)") );
    image.load(imagePath);

}

void NewQuestion::on_soundAddButton_clicked()
{
    ui->soundAddButton->setEnabled(false);
    ui->soundAddButton->setText("Sound added");
    soundPath = QFileDialog::getOpenFileName(this, "Open Sound", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("Wav file (*.wav)") );
}
