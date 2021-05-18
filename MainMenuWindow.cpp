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
    User *new_user = new User();
    users.append(new_user);
    user = users[0];
    //coursesCounter = 0;
}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}
void MainMenuWindow::updateCoursesInComboBox()
{
    ui->coursesComboBox->clear();
    for(int i = 0; i < user->getCoursesListSize(); i++)
    {   
       // QString courseName = coursesList[i]->getName();
        QString courseName = user->getCourse(i)->getName();
        ui->coursesComboBox->addItem(courseName);
    }
}

void MainMenuWindow::on_newCourseButton_clicked()
{
    //LearningWindow dialog(coursesList, ui->courseNameTextEdit->toPlainText(), this);
    LearningWindow dialog(user->getCoursesList(), ui->courseNameTextEdit->toPlainText(), this);
    dialog.setWindowTitle("SuperMemo");
    if(dialog.exec())
    {
        ui->coursesComboBox->setEnabled(true);
        ui->openCourseButton->setEnabled(true);
        updateCoursesInComboBox();
    }
}

/*void MainMenuWindow::printCourses()
{
    for(int i = 0; i < user->getCoursesListSize(); i++)
    {
        coursesList[i]->printCourse();
    }
}*/

void MainMenuWindow::on_actionPrint_Courses_to_console_triggered()
{
   // printCourses();
    for(int i=0; i < users.size(); i++)
    {
        QTextStream(stdout) <<"---------- User: "<< users[i]->getName() <<" ------------------"<< Qt::endl;
        users[i]->printCourses();
    }
}

void MainMenuWindow::on_openCourseButton_clicked()
{
    LearningWindow dialog(user->getCoursesList(), ui->coursesComboBox->currentIndex(), this);
    dialog.setWindowTitle("SuperMemo");
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
    for(int i = 0; i < user->getCoursesListSize(); i++)
    {
       // coursesList[i]->simulateTime(-7);
        user->getCourse(i)->simulateTime(-7);
    }
}

QList <User*> &MainMenuWindow::getUsersList()
{
    return users;
}


void MainMenuWindow::on_actionChange_User_triggered()
{
    ChangeUserWindow dialog(getUsersList(), this);
    dialog.setWindowTitle("Change user");
    if(dialog.exec())
    {
        if(user != dialog.getCurrentUser())
        {
            user = dialog.getCurrentUser();
            userChanged();
        }


    }
}

void MainMenuWindow::userChanged()
{
    updateCoursesInComboBox();
    ui->courseNameTextEdit->clear();
    if(ui->coursesComboBox->count() == 0)
    {
        ui->coursesComboBox->setEnabled(false);
        ui->openCourseButton->setEnabled(false);
    }
    else
    {
        ui->coursesComboBox->setEnabled(true);
        ui->openCourseButton->setEnabled(true);
    }
}
