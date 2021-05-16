#include "MainMenuWindow.h"
#include "ui_MainMenuWindow.h"
#include <unistd.h>
MainMenuWindow::MainMenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenuWindow)
{
    ui->setupUi(this);
    coursesCounter = 0;

}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}
void MainMenuWindow::updateCoursesInComboBox()
{
    QTextStream(stdout) << "update:  " << Qt::endl<< Qt::endl<< Qt::endl;
    ui->coursesComboBox->clear();
    for(int i = 0; i < coursesList.size(); i++)
    {
        QTextStream(stdout) <<  i << Qt::endl;
        QTextStream(stdout) << coursesList.size() << Qt::endl;
        QString courseName = coursesList[i]->getName();
        QTextStream(stdout) << courseName << Qt::endl;
        //ui->coursesComboBox->addItem(courseName);
        //ui->coursesComboBox->addItem("coursesList[i]");
        //sleep(2);

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
    QTextStream(stdout) << "przed 1 append" << Qt::endl;
   // coursesList.append(c);
    LearningWindow dialog(coursesList, ui->courseNameTextEdit->toPlainText(), this);
    if(dialog.exec() )
    {
       //QTextStream(stdout) << "otwarto ekran pytania" << Qt::endl;
       //on_newQuestionAdded(dialog.getQuestion(), dialog.getAnswer(), dialog.getImage(), dialog.getSoundPath());
    }
}

void MainMenuWindow::on_actionUpdateCB_triggered()
{
    updateCoursesInComboBox();
}
