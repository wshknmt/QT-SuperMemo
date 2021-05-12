#include "MainMenuWindow.h"
#include "ui_MainMenuWindow.h"

MainMenuWindow::MainMenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenuWindow)
{
    ui->setupUi(this);
}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}

void MainMenuWindow::on_actionNew_course_triggered()
{
    Course *c = new Course(this);
    coursesList.append(c);
    //MainWindow *dialog = new MainWindow(coursesList, this);
    LearningWindow dialog(coursesList, this);
    /*nq = new NewQuestion(this);
    nq->setWindowTitle("Add new question");
    connect(nq, &NewQuestion::newQuestionReady, this, &MainWindow::on_newQuestionAdded);
    nq->show();*/
    if(dialog.exec() )
    {
        //QTextStream(stdout) << "otwarto ekran pytania" << Qt::endl;
        //on_newQuestionAdded(dialog.getQuestion(), dialog.getAnswer(), dialog.getImage(), dialog.getSoundPath());
    }
    //dialog->show();
    //QTextStream(stdout) << "otwarto ekran uczenia" << Qt::endl;
    /*if(dialog->exec() )
    {

    }*/


}
