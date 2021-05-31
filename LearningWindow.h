#ifndef LEARNINGWINDOW_H
#define LEARNINGWINDOW_H

#include <QDialog>
#include <QtMultimedia/QSound>
#include <QDate>
#include <QTextStream>
#include <QMenu>
#include "NewQuestion.h"
#include "Card.h"
#include "Course.h"
#include "CoursesManager.h"

namespace Ui {
    class LearningWindow;
}

class LearningWindow : public QDialog {
    Q_OBJECT

public:
    LearningWindow(CoursesManager &cManager, QString courseName, QFont font, QWidget *parent = nullptr);
    LearningWindow(CoursesManager &cManager, int numberOfSelectedCourse, QFont font, QWidget *parent = nullptr);
    ~LearningWindow();
    void setDefaultImage();
    void checkImage();
    void setDefaultValues();
    void setImage(QPixmap image);
    void updateProgressBar();
    void updateStatusLabel();
    bool isEqualToCurrentDate(QDate date);

signals:
    void questionAvailable();

private slots:
    void on_showAnswerButton_clicked();
    void on_newQuestionAdded(QString, QString, QPixmap, QString);
    void on_startLearning();
    void on_yesButton_clicked();
    void on_noButton_clicked();
    void on_playButton_clicked();
    void on_stopButton_clicked();
    void on_newQuestionButton_clicked();
    void on_deleteButton_clicked();
    void on_endButton_clicked();
    void on_almostButton_clicked();

private:
    Ui::LearningWindow *ui_;

    Card *card_;
    Course *course_;
    QSound *sound_;
   // int courseNumber_;
    //QList <Course*> *coursesList_;
    CoursesManager *coursesManager_;
    QFont font_;
};

#endif // LEARNINGWINDOW_H
