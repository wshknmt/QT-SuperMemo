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

namespace Ui {
class LearningWindow;
}

class LearningWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LearningWindow(QWidget *parent = nullptr);
    LearningWindow(QList <Course*> &coursesList, QString courseName, QWidget *parent = nullptr);
    LearningWindow(QList <Course*> &coursesList, int numberOfSelectedCourse, QWidget *parent = nullptr);
    ~LearningWindow();
    void setDefaultImage();
    void checkImage();
    void setDefaultValues();
    void setImage(QPixmap image);
    void updateProgressBar();
    void updateStatusLabel();
    void updateCoursesList();
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

private:
    Ui::LearningWindow *ui;
    NewQuestion *nq;
    Card *newCard;
    Card *card;
    Course *course;
    QSound *sound;
    int courseNumber;
    QList <Course*> *coursesList;
};

#endif // LEARNINGWINDOW_H
