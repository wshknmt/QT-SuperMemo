#include "MainMenuWindow.h"
#include "ui_MainMenuWindow.h"
#include "UserCalendarWindow.h"

MainMenuWindow::MainMenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainMenuWindow)
{
    ui_->setupUi(this);
    ui_->coursesComboBox->setEnabled(false);
    ui_->openCourseButton->setEnabled(false);
    ui_->actionDelete_selected_course->setEnabled(false);
    ui_->actionImport->setEnabled(false);
    ui_->actionExport->setEnabled(false);
    ui_->actionHelp->setEnabled(false);
    ui_->newCourseButton->setEnabled(false);
    font_ = QFont( "MS Shell Dlg 2", 15 );
    //if(!isSaveEmpty())
    if(false)
        readFromFile();//crashuje sie
    else {
        User *new_user = new User();
        users_.append(new_user);
        user_ = users_[0];
        ui_->userDisplayLabel->setText(user_->getName());
        QFont f;
        f.setBold(true);
        ui_->userDisplayLabel->setFont(f);
    }
}

MainMenuWindow::~MainMenuWindow() {
    delete ui_;
}
void MainMenuWindow::updateCoursesInComboBox() {
    ui_->coursesComboBox->clear();
    for(int i = 0; i < user_->getCourseManager().getCoursesNumber(); i++) {
        QString courseName = user_->getCourseManager().getCourse(i)->getName();
        ui_->coursesComboBox->addItem(courseName);
    }
}

void MainMenuWindow::on_newCourseButton_clicked() {
    LearningWindow dialog(user_->getCourseManager(), ui_->courseNameTextEdit->toPlainText(), font_, this);
    dialog.setWindowTitle("SuperMemo");
    if(dialog.exec()) {
        ui_->coursesComboBox->setEnabled(true);
        ui_->openCourseButton->setEnabled(true);
        updateCoursesInComboBox();
    }
    ui_->courseNameTextEdit->clear();
}

void MainMenuWindow::on_actionPrint_Courses_to_console_triggered() {
    for(int i=0; i < users_.size(); i++) {
        QTextStream(stdout) <<"---------- User: "<< users_[i]->getName() <<" ------------------"<< Qt::endl;
        users_[i]->print();
    }
}

void MainMenuWindow::on_openCourseButton_clicked() {
    LearningWindow dialog(user_->getCourseManager(), ui_->coursesComboBox->currentIndex(), font_, this);
    dialog.setWindowTitle("SuperMemo");
    if(dialog.exec()) {

    }
}

void MainMenuWindow::on_actionExit_triggered() {
    QCoreApplication::quit();
}

void MainMenuWindow::on_warpTimeButton_clicked() {
    for(int i = 0; i < user_->getCourseManager().getCoursesNumber(); i++) {
        user_->getCourseManager().getCourse(i)->simulateTime(-7);
    }
}

QList <User*> &MainMenuWindow::getUsersList() {
    return users_;
}

void MainMenuWindow::on_actionChange_User_triggered() {
    ChangeUserWindow dialog(users_, this);
    dialog.setWindowTitle("Wybierz użytkownika");
    if(dialog.exec()) {
        if(user_ != dialog.getCurrentUser()) {
            user_ = dialog.getCurrentUser();
            userChanged();
        }
    }
}

void MainMenuWindow::userChanged() {
    updateCoursesInComboBox();
    ui_->courseNameTextEdit->clear();
    ui_->userDisplayLabel->setText(user_->getName());
    if(ui_->coursesComboBox->count() == 0) {
        ui_->coursesComboBox->setEnabled(false);
        ui_->openCourseButton->setEnabled(false);
    }
    else {
        ui_->coursesComboBox->setEnabled(true);
        ui_->openCourseButton->setEnabled(true);
    }
}

void MainMenuWindow::saveToFile() {
    std::ofstream output_file;
    output_file.open("save.txt", std::ios::trunc);
    for(int i=0; i < users_.size(); i++)
    {
        User u;
        u.setName(users_[i]->getName());
        //u.setCoursesList(users[i]->getCoursesList());
        output_file.write((char*)&u, sizeof(User));

    }
    output_file.close();
    QTextStream(stdout) <<"saved"<< Qt::endl;
}

void MainMenuWindow::readFromFile() {

    std::ifstream input_file;
    input_file.open("save.txt", std::ios::in);

    //user = new User();
    //User usr;
    QTextStream(stdout) <<"file opened"<< Qt::endl;
    while(!input_file.eof()) {
        User u;
        input_file.read((char*)&u, sizeof(User));

        user_ = new User();
        user_->setName(u.getName());
        QTextStream(stdout) <<"xx"<< Qt::endl;
       // user->setCoursesList(u.getCoursesList());
        users_.append(user_);
        QTextStream(stdout) <<"name user: "<<user_->getName()<< Qt::endl;
    }

    input_file.close();
    user_ = users_[0];

    userChanged();
}

bool MainMenuWindow::isSaveEmpty() {
    std::ifstream input_file;
    input_file.open("save.txt", std::ios::in);
    bool result = (input_file.peek() == std::ifstream::traits_type::eof());
    input_file.close();
    return result;
}

void MainMenuWindow::on_actionSave_triggered() {
    //saveToFile();

}

void MainMenuWindow::on_actionSettings_triggered() {
    SettingsWindow dialog(this);
    dialog.setWindowTitle("Ustawienia");
    if(dialog.exec()) {
        font_ = dialog.getFont();
    }
}

void MainMenuWindow::on_openCalendarButton_clicked() {
    UserCalendarWindow dialog(user_->getCourseManager(), this);
    dialog.setWindowTitle("Kalendarz kursów");
    if(dialog.exec()) {

    }
}

void MainMenuWindow::on_courseNameTextEdit_textChanged() {
    QString courseName = ui_->courseNameTextEdit->toPlainText();
    bool originalName = true;
    if(courseName.size() > 0) {
        for(int i=0; i < user_->getCourseManager().getCoursesNumber(); i++) {
            if(user_->getCourseManager().getCourse(i)->getName() == courseName) {
                originalName = false;
                break;
            }
        }
        if(originalName) {
            ui_->newCourseButton->setEnabled(true);
            return;
        }
    }
    ui_->newCourseButton->setEnabled(false);
}
