#include "MainMenuWindow.h"
#include "ui_MainMenuWindow.h"
#include <unistd.h>
MainMenuWindow::MainMenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenuWindow)
{
    ui->setupUi(this);
    ui->coursesComboBox->setEnabled(false);
    ui->openCourseButton->setEnabled(false);
    coursesCounter = 0;
}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}
void MainMenuWindow::updateCoursesInComboBox()
{
    ui->coursesComboBox->clear();
    for(int i = 0; i < coursesList.size(); i++)
    {   
        QString courseName = coursesList[i]->getName();
        ui->coursesComboBox->addItem(courseName);
    }
}

void MainMenuWindow::on_newCourseButton_clicked()
{
    LearningWindow dialog(coursesList, ui->courseNameTextEdit->toPlainText(), this);
    if(dialog.exec())
    {
        ui->coursesComboBox->setEnabled(true);
        ui->openCourseButton->setEnabled(true);
        updateCoursesInComboBox();
    }
}

void MainMenuWindow::printCourses()
{
    for(int i = 0; i < coursesList.size(); i++)
    {
        coursesList[i]->printCourse();
    }
}

void MainMenuWindow::on_actionPrint_Courses_to_console_triggered()
{
    printCourses();
}

void MainMenuWindow::on_openCourseButton_clicked()
{
    LearningWindow dialog(coursesList, ui->coursesComboBox->currentIndex(), this);
    if(dialog.exec())
    {

    }
}

void MainMenuWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void MainMenuWindow::on_warpTimeButton_clicked()
{
    for(int i = 0; i < coursesList.size(); i++)
    {
        coursesList[i]->simulateTime(-7);
    }
}
