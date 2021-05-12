#ifndef LEARNINGWINDOW_H
#define LEARNINGWINDOW_H

#include <QDialog>
#include <QtMultimedia/QSound>
#include <QDate>
#include <QTextStream>
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
    LearningWindow(QList <Course*> &coursesList, QWidget *parent = nullptr);
    LearningWindow(QList <Course*> &coursesList, int numberOfSelectedCourse, QWidget *parent = nullptr);
    ~LearningWindow();
    void setDefaultImage();
    void setDefaultValues();
    void setImage(QPixmap image);
    void updateProgressBar();
    void updateStatusLabel();
    void updateCoursesList();
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

    void on_pushButton_clicked();

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
