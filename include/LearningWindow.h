/*
 * File name: LearningWindow.h
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class implementing functions for questions answering window.
 */

#ifndef LEARNINGWINDOW_H
#define LEARNINGWINDOW_H

#include <QDialog>
#include <QtMultimedia/QSound>
#include <QDate>
#include <QMenu>

#include "NewQuestion.h"
#include "Card.h"
#include "Course.h"
#include "CoursesManager.h"
#include "UserStats.h"

namespace Ui {
    class LearningWindow;
}

class LearningWindow : public QDialog {
    Q_OBJECT

public:
    LearningWindow(CoursesManager &cManager, UserStats &uStats, QString courseName, QWidget *parent = nullptr);
    LearningWindow(CoursesManager &cManager, UserStats &uStats, int numberOfSelectedCourse, QWidget *parent = nullptr);
    ~LearningWindow();
    void setDefaultImage();
    void setDefaultValues();
    void setImage(QPixmap image);
    void updateProgressBar();
    void updateStatusLabel();
    bool isEqualToCurrentDate(QDate date) const;
    int getProgressBarValue() const;
    void answerRated();

signals:
    void questionAvailable();

private slots:
    void on_showAnswerButton_clicked();
    void on_newQuestionAdded(QString, QString, QString, QString);
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
    CoursesManager *coursesManager_;
    UserStats *userStats_;
};

#endif // LEARNINGWINDOW_H
