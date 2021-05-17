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
    //QTextStream(stdout) << "update:  " << Qt::endl<< Qt::endl<< Qt::endl;
    ui->coursesComboBox->clear();
    //QTextStream(stdout) <<"  size:  "<< coursesList.size() << Qt::endl;
    for(int i = 0; i < coursesList.size(); i++)
    {
        //QTextStream(stdout) <<  i << Qt::endl;
        //QTextStream(stdout) <<"  counter:  "<< coursesList[i]->getCardsCounter() << Qt::endl;
        QString courseName = coursesList[i]->getName();
        //QTextStream(stdout) << courseName << Qt::endl;
        ui->coursesComboBox->addItem(courseName);

        //ui->coursesComboBox->


    }

}

void MainMenuWindow::on_actionNew_course_triggered()
{
   /* Course *c = new Course("kurs1", this);
    coursesList.append(c);
    LearningWindow dialog(coursesList, this);
*/
    /*nq = new NewQuestion(this);
    nq->setWindowTitle("Add new question");
    connect(nq, &NewQuestion::newQuestionReady, this, &MainWindow::on_newQuestionAdded);
    nq->show();*/

    /*if(dialog.exec() )
    {
       //QTextStream(stdout) << "otwarto ekran pytania" << Qt::endl;
       //on_newQuestionAdded(dialog.getQuestion(), dialog.getAnswer(), dialog.getImage(), dialog.getSoundPath());
    }*/
    //dialog->show();
    /*if(dialog->exec() )
    {

    }*/


}

void MainMenuWindow::on_newCourseButton_clicked()
{
    /*Course *c;
    if(ui->courseNameTextEdit->toPlainText().isEmpty())
        c = new Course(this);
    else
        c = new Course(ui->courseNameTextEdit->toPlainText(), this);*/
   // QTextStream(stdout) << "przed 1 append" << Qt::endl;
   // coursesList.append(c);
    LearningWindow dialog(coursesList, ui->courseNameTextEdit->toPlainText(), this);
    if(dialog.exec())
    {
        ui->coursesComboBox->setEnabled(true);
        ui->openCourseButton->setEnabled(true);
        updateCoursesInComboBox();
        //QTextStream(stdout) << "updated" << Qt::endl;
    }
}

void MainMenuWindow::on_actionUpdateCB_triggered()
{
    //updateCoursesInComboBox();
    //QTextStream(stdout) << ui->coursesComboBox->currentIndex() << Qt::endl;
}

void MainMenuWindow::printCourses()
{
    for(int i = 0; i < coursesList.size(); i++)
    {
        //QTextStream(stdout) <<  i << Qt::endl;
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
    //dialog.setDefaultImage();
    if(dialog.exec())
    {
       // ui->coursesComboBox->setEnabled(true);
        //ui->openCourseButton->setEnabled(true);
        //updateCoursesInComboBox();
        //QTextStream(stdout) << "updated" << Qt::endl;
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
