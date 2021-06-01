#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>
#include <fstream>
#include "Card.h"
#include "Course.h"
#include "LearningWindow.h"
#include "User.h"
#include "ChangeUserWindow.h"
#include "SettingsWindow.h"

namespace Ui {
    class MainMenuWindow;
}

class MainMenuWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainMenuWindow(QWidget *parent = nullptr);
    ~MainMenuWindow();
    void updateCoursesInComboBox();
    QList <User*> &getUsersList();
    void userChanged();
    void saveToFile();
    void readFromFile();
    bool isSaveEmpty();
    void updateProgressBar(int number);

private slots:
    void on_newCourseButton_clicked();
    void on_actionPrint_Courses_to_console_triggered();
    void on_openCourseButton_clicked();
    void on_actionExit_triggered();
    void on_warpTimeButton_clicked();
    void on_actionChange_User_triggered();
    void on_actionSave_triggered();
    void on_actionSettings_triggered();
    void on_openCalendarButton_clicked();
    void on_courseNameTextEdit_textChanged();
    void on_statsButton_clicked();
    void on_coursesComboBox_highlighted(int index);
    void on_extraReviewButton_clicked();

    void on_activityStatsButton_clicked();

private:
    Ui::MainMenuWindow *ui_;
    QList <User*> users_;
    User *user_;
    QFont font_;
};

#endif // MAINMENUWINDOW_H
