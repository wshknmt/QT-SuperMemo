#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NewQuestion.h"
#include "Card.h"
#include "Course.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setDefaultImage();
    void updateProgressBar();
signals:
    void questionAvailable();
private slots:

    void on_actionNew_question_triggered();

    void on_actionExit_triggered();

    void on_showAnswerButton_clicked();

    void on_newQuestionAdded(QString, QString);

    void on_startLearning();

    void on_yesButton_clicked();

    void on_noButton_clicked();

    void on_actionDelete_Question_triggered();

private:
    Ui::MainWindow *ui;
    NewQuestion *nq;
    Card *newCard;
    Card *card;
    Course *course;
};
#endif // MAINWINDOW_H
