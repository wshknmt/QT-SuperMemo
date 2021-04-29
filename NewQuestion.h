#ifndef NEWQUESTION_H
#define NEWQUESTION_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class NewQuestion;
}

class NewQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit NewQuestion(QWidget *parent = nullptr);
    ~NewQuestion();
    QString getQuestion();
    QString getAnswer();

signals:
    void newQuestionReady(QString, QString, QPixmap, QString);

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_textEdit_2_textChanged();

    void on_textEdit_textChanged();

    void on_imageAddButton_clicked();

    void on_soundAddButton_clicked();

private:
    Ui::NewQuestion *ui;
    QString question;
    QString answer;
    QString imagePath;
    QPixmap image;
    QString soundPath;
};

#endif // NEWQUESTION_H
