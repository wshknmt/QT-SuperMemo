#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>
#include "Card.h"
#include "Course.h"
#include "LearningWindow.h"
#include "User.h"

namespace Ui {
class MainMenuWindow;
}

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenuWindow(QWidget *parent = nullptr);
    ~MainMenuWindow();
    void updateCoursesInComboBox();
    //void printCourses();

private slots:

    void on_newCourseButton_clicked();

    void on_actionPrint_Courses_to_console_triggered();

    void on_openCourseButton_clicked();

    void on_actionExit_triggered();

    void on_warpTimeButton_clicked();

private:
    Ui::MainMenuWindow *ui;
    //QList <Course*> coursesList;
    QList <User*> users;
    User *user;
    //int coursesCounter;
};

#endif // MAINMENUWINDOW_H
