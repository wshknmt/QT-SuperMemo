#ifndef NEWQUESTION_H
#define NEWQUESTION_H

#include <QDialog>

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


private:
    Ui::NewQuestion *ui;
    QString question;
    QString answer;
};

#endif // NEWQUESTION_H
