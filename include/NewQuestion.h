/*
 * File name: NewQuestion.h
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class implementing functions for new questions adding window.
 */

#ifndef NEWQUESTION_H
#define NEWQUESTION_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
    class NewQuestion;
}

class NewQuestion : public QDialog {
    Q_OBJECT

public:
    explicit NewQuestion(QWidget *parent = nullptr);
    ~NewQuestion();
    QString getQuestion() const;
    QString getAnswer() const;
    QString getImagePath() const;
    QString getSoundPath() const;

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_textEdit_2_textChanged();
    void on_textEdit_textChanged();
    void on_imageAddButton_clicked();
    void on_soundAddButton_clicked();

private:
    Ui::NewQuestion *ui_;
    QString question_;
    QString answer_;
    QString imagePath_;
    QString soundPath_;
};

#endif // NEWQUESTION_H
