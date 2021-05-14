#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>
#include "Card.h"
#include "Course.h"
#include "LearningWindow.h"

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

private slots:
    void on_actionNew_course_triggered();

    void on_newCourseButton_clicked();

    void on_actionUpdateCB_triggered();

private:
    Ui::MainMenuWindow *ui;
    QList <Course*> coursesList;
    int coursesCounter;
};

#endif // MAINMENUWINDOW_H
