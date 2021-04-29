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
    void newQuestionReady(QString, QString);

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_textEdit_2_textChanged();

    void on_textEdit_textChanged();

private:
    Ui::NewQuestion *ui;
    QString question;
    QString answer;
};

#endif // NEWQUESTION_H
