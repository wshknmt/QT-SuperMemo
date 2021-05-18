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
    ui->actionDelete_selected_course->setEnabled(false);
    ui->actionImport->setEnabled(false);
    ui->actionExport->setEnabled(false);
    ui->actionHelp->setEnabled(false);
    font = QFont( "MS Shell Dlg 2", 15 );
    //if(!isSaveEmpty())
    if(false)
    {
        readFromFile();//crashuje sie
    }
    else
    {
        QTextStream(stdout) <<"Plik byl pusty "<< Qt::endl;
        User *new_user = new User();
        users.append(new_user);
        user = users[0];
        ui->userDisplayLabel->setText(user->getName());
        QFont f;
        f.setBold(true);
        ui->userDisplayLabel->setFont(f);
    }
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
        QString courseName = user->getCourse(i)->getName();
        ui->coursesComboBox->addItem(courseName);
    }
}

void MainMenuWindow::on_newCourseButton_clicked()
{
    LearningWindow dialog(user->getCoursesList(), ui->courseNameTextEdit->toPlainText(), font, this);
    dialog.setWindowTitle("SuperMemo");
    if(dialog.exec())
    {
        ui->coursesComboBox->setEnabled(true);
        ui->openCourseButton->setEnabled(true);
        updateCoursesInComboBox();
    }
    ui->courseNameTextEdit->clear();
}

void MainMenuWindow::on_actionPrint_Courses_to_console_triggered()
{
    for(int i=0; i < users.size(); i++)
    {
        QTextStream(stdout) <<"---------- User: "<< users[i]->getName() <<" ------------------"<< Qt::endl;
        users[i]->printCourses();
    }
}

void MainMenuWindow::on_openCourseButton_clicked()
{
    LearningWindow dialog(user->getCoursesList(), ui->coursesComboBox->currentIndex(), font, this);
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
    ui->userDisplayLabel->setText(user->getName());
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

void MainMenuWindow::saveToFile()
{
    std::ofstream output_file;
    output_file.open("save.txt", std::ios::trunc);
    for(int i=0; i < users.size(); i++)
    {
        User u;
        u.setName(users[i]->getName());
        //u.setCoursesList(users[i]->getCoursesList());
        output_file.write((char*)&u, sizeof(User));

    }
    output_file.close();
    QTextStream(stdout) <<"saved"<< Qt::endl;
}

void MainMenuWindow::readFromFile()
{

    std::ifstream input_file;
    input_file.open("save.txt", std::ios::in);

    //user = new User();
    //User usr;
    QTextStream(stdout) <<"file opened"<< Qt::endl;
    while(!input_file.eof())
    {
        User u;
        input_file.read((char*)&u, sizeof(User));

        user = new User();
        user->setName(u.getName());
        QTextStream(stdout) <<"xx"<< Qt::endl;
       // user->setCoursesList(u.getCoursesList());
        users.append(user);
        QTextStream(stdout) <<"name user: "<<user->getName()<< Qt::endl;
    }

    input_file.close();
    user = users[0];

    userChanged();

}

bool MainMenuWindow::isSaveEmpty()
{
    std::ifstream input_file;
    input_file.open("save.txt", std::ios::in);
    bool result = (input_file.peek() == std::ifstream::traits_type::eof());
    input_file.close();
    return result;
}

void MainMenuWindow::on_actionSave_triggered()
{
    //saveToFile();

}

void MainMenuWindow::on_actionSettings_triggered()
{
    SettingsWindow dialog(this);
    dialog.setWindowTitle("Settings");
    if(dialog.exec())
    {
        font = dialog.getFont();
    }
}
