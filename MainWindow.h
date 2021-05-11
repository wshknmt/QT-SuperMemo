#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QSound>
#include <QDate>
#include <QTextStream>
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
    MainWindow(QList <Course*> &coursesList, QWidget *parent = nullptr);
    MainWindow(QList <Course*> &coursesList, int numberOfSelectedCourse, QWidget *parent = nullptr);
    ~MainWindow();
    void setDefaultImage();
    void setDefaultValues();
    void setImage(QPixmap image);
    void updateProgressBar();
    void updateStatusLabel();
signals:
    void questionAvailable();
private slots:

    void on_actionNew_question_triggered();

    void on_actionExit_triggered();

    void on_showAnswerButton_clicked();

    void on_newQuestionAdded(QString, QString, QPixmap, QString);

    void on_startLearning();

    void on_yesButton_clicked();

    void on_noButton_clicked();

    void on_actionDelete_Question_triggered();

    void on_playButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::MainWindow *ui;
    NewQuestion *nq;
    Card *newCard;
    Card *card;
    Course *course;
    QSound *sound;
    int courseNumber;
    QList <Course*> *courseList;
    //auto *coursesListt;
};
#endif // MAINWINDOW_H
