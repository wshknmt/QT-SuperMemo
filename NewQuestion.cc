#include <QFileDialog>
#include <QStandardPaths>
#include "NewQuestion.h"
#include "ui_NewQuestion.h"

NewQuestion::NewQuestion(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::NewQuestion)
{
    ui_->setupUi(this);
    QPixmap img1(":/images/Icons/photo.png");
    QPixmap img2(":/images/Icons/sound.png");
    ui_->imageAddButton->setIcon(img1);
    ui_->soundAddButton->setIcon(img2);
    ui_->okButton->setEnabled(false);
    answer_ = "";
    question_ = "";
    soundPath_.clear();
}

NewQuestion::~NewQuestion() {
    delete ui_;
}

QString NewQuestion::getQuestion() {
    return question_;
}

QString NewQuestion::getAnswer() {
    return answer_;
}
QPixmap NewQuestion::getImage() {
    return image_;
}
QString NewQuestion::getImagePath() {
    return " ";
}
QString NewQuestion::getSoundPath() {
    return soundPath_;
}

void NewQuestion::on_okButton_clicked() {
    answer_ = ui_->textEdit->toPlainText();
    question_ = ui_->textEdit_2->toPlainText();
    accept();
}

void NewQuestion::on_cancelButton_clicked() {
    QMessageBox msg;
    msg.setText("Jesteś pewien że chcesz anulować dodawanie pytania?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    int ret = msg.exec();
    if (ret == QMessageBox::Yes)
        reject();
}

void NewQuestion::on_textEdit_2_textChanged() {
    if(ui_->textEdit_2->toPlainText().length() >= 1 && ui_->textEdit->toPlainText().length() >= 1)
        ui_->okButton->setEnabled(true);
    else
        ui_->okButton->setEnabled(false);
}

void NewQuestion::on_textEdit_textChanged() {
    if(ui_->textEdit_2->toPlainText().length() >= 1 && ui_->textEdit->toPlainText().length() >= 1)
        ui_->okButton->setEnabled(true);
    else
        ui_->okButton->setEnabled(false);
}

void NewQuestion::on_imageAddButton_clicked() {
    imagePath_ = QFileDialog::getOpenFileName(this,
        "Otwórz zdjęcie", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("Plik JPG (*.jpg *.jpeg);; Plik PNG  (*.png);; Plik BMP (*.bmp)") );
    if(imagePath_.size() != 0) {
      image_.load(imagePath_);
      ui_->imageAddButton->setEnabled(false);
      ui_->imageAddButton->setText("Zdjęcie dodane");
    }
}

void NewQuestion::on_soundAddButton_clicked() {
    soundPath_ = QFileDialog::getOpenFileName(this, "Otwórz dźwięk", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("Plik Wav (*.wav)") );
    if(soundPath_.size() != 0) {
        ui_->soundAddButton->setEnabled(false);
        ui_->soundAddButton->setText("Dźwięk dodany");
    }
}
