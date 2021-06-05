/*
 * File name: MainMenuWindow.cc
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class implementing functions for main menu window.
 */

#include "MainMenuWindow.h"
#include "ui_MainMenuWindow.h"
#include "UserCalendarWindow.h"
#include "TypesOfAnswerStatisticsWindow.h"
#include "ActivityStatisticsWindow.h"

MainMenuWindow::MainMenuWindow(QWidget *parent) :
    QMainWindow(parent), ui_(new Ui::MainMenuWindow)
{
    ui_->setupUi(this);
    ui_->coursesComboBox->setEnabled(false);
    ui_->openCourseButton->setEnabled(false);
    ui_->extraReviewButton->setEnabled(false);
    ui_->actionDelete_selected_course->setEnabled(false);
    ui_->actionImport->setEnabled(true);
    ui_->actionExport->setEnabled(false);
    ui_->actionHelp->setEnabled(false);
    ui_->progressBar->setValue(0);
    ui_->progressBar->setEnabled(false);
    ui_->newCourseButton->setEnabled(false);
    ui_->questionsToRepeatCounter->setText(QString(" "));
    Settings::getInstance()->setFont(QFont( "MS Shell Dlg 2", 15 ));
    User *new_user = new User();
    users_.append(new_user);
    user_ = users_[0];
    ui_->userDisplayLabel->setText(user_->getName());
    QFont f;
    f.setBold(true);
    ui_->userDisplayLabel->setFont(f);
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
    if(ui_->coursesComboBox->count() > 0)
        updateProgressBar(0);
}

void MainMenuWindow::on_newCourseButton_clicked() {
    LearningWindow dialog(user_->getCourseManager(), user_->getUserStats(), ui_->courseNameTextEdit->toPlainText(), this);
    dialog.setWindowTitle("SuperMemo");
    dialog.setDefaultImage();
    if(dialog.exec()) {
        updateWindow();
        /*ui_->coursesComboBox->setEnabled(true);
        ui_->openCourseButton->setEnabled(true);
        ui_->extraReviewButton->setEnabled(true);
        ui_->actionExport->setEnabled(true);
        updateCoursesInComboBox();*/
    }
    ui_->courseNameTextEdit->clear();
}

void MainMenuWindow::on_actionPrint_Courses_to_console_triggered() {
    /*for(int i=0; i < users_.size(); i++) {
        QTextStream(stdout) <<"---------- User: "<< users_[i]->getName() <<" ------------------"<< Qt::endl;
        users_[i]->print();
    }*/
}

void MainMenuWindow::on_openCourseButton_clicked() {
    LearningWindow dialog(user_->getCourseManager(), user_->getUserStats(), ui_->coursesComboBox->currentIndex(), this);
    dialog.setWindowTitle("SuperMemo");
    if(dialog.exec()) {
        updateWindow();
    }
}

void MainMenuWindow::on_actionExit_triggered() {
    QCoreApplication::quit();
}

QList<User*> &MainMenuWindow::getUsersList() {
    return users_;
}

void MainMenuWindow::on_actionChange_User_triggered() {
    ChangeUserWindow dialog(users_, this);
    dialog.setWindowTitle("Wybierz użytkownika");
    if(dialog.exec()) {
        if(user_ != dialog.getCurrentUser()) {
            user_ = dialog.getCurrentUser();
            updateWindow();
        }
    }
}

void MainMenuWindow::updateWindow() {
    ui_->progressBar->setValue(0);
    ui_->progressBar->setEnabled(false);
    ui_->questionsToRepeatCounter->setText(QString(" "));
    updateCoursesInComboBox();
    ui_->courseNameTextEdit->clear();
    ui_->userDisplayLabel->setText(user_->getName());
    if(ui_->coursesComboBox->count() == 0) {
        ui_->coursesComboBox->setEnabled(false);
        ui_->openCourseButton->setEnabled(false);
        ui_->extraReviewButton->setEnabled(false);
        ui_->actionExport->setEnabled(false);
        ui_->actionDelete_selected_course->setEnabled(false);
    }
    else {
        ui_->coursesComboBox->setEnabled(true);
        ui_->openCourseButton->setEnabled(true);
        ui_->extraReviewButton->setEnabled(true);
        ui_->actionExport->setEnabled(true);
        ui_->actionDelete_selected_course->setEnabled(true);
    }
}

void MainMenuWindow::saveToFile() {
    std::fstream file("save.dat", std::ios_base::out | std::ios_base::binary);
    for(int i=0; i < users_.size(); i++) {
        User u;
        u.setName(users_[i]->getName());
        u.setCourseManager(users_[i]->getCourseManager());
        u.setUserStats(users_[i]->getUserStats());
        u.serialize(file, true);
    }
}


void MainMenuWindow::readFromFile() {
    std::ifstream input_file;
    input_file.open("save.txt", std::ios::in);

    while(!input_file.eof()) {
        User u;
        input_file.read((char*)&u, sizeof(User));
        user_ = new User();
        user_->setName(u.getName());
        users_.append(user_);
    }
    input_file.close();
    user_ = users_[0];
    updateWindow();
}

bool MainMenuWindow::isSaveEmpty() {
    std::ifstream input_file;
    input_file.open("save.txt", std::ios::in);
    bool result = (input_file.peek() == std::ifstream::traits_type::eof());
    input_file.close();
    return result;
}

void MainMenuWindow::on_actionSave_triggered() {
    saveToFile();
}

void MainMenuWindow::on_actionSettings_triggered() {
    SettingsWindow dialog(this);
    dialog.setWindowTitle("Ustawienia");
    dialog.exec();
}

void MainMenuWindow::on_openCalendarButton_clicked() {
    UserCalendarWindow dialog(user_->getCourseManager(), user_->getUserStats(), this);
    dialog.setWindowTitle("Kalendarz kursów");
    if(dialog.exec()) {
        updateWindow();
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

void MainMenuWindow::on_statsButton_clicked() {
    TypesOfAnswerStatisticsWindow dialog(user_->getUserStats(), this);
    dialog.setWindowTitle("Statystyki poprawności udzielalnych odpowiedzi");
    dialog.exec();
}

void MainMenuWindow::updateProgressBar(int number) {
    Course *course = user_->getCourseManager().getCourse(number);
    course->countProgress();
    ui_->progressBar->setValue(course->getProgress());
    if(course->getSizeCardsToRepeat() == 0)
        ui_->questionsToRepeatCounter->setText(QString(" "));
    else
        ui_->questionsToRepeatCounter->setText(QString("Liczba pytań do powtórzenia w tym kursie: " + QString::number(course->getSizeCardsToRepeat())));
}

void MainMenuWindow::on_coursesComboBox_highlighted(int index) {
    if(user_->getCourseManager().getCourse(index)->getCardsCounter() == 0)
        ui_->progressBar->setEnabled(false);
    else
        ui_->progressBar->setEnabled(true);
    updateProgressBar(index);
}

void MainMenuWindow::on_extraReviewButton_clicked() {
    user_->getCourseManager().getCourse(ui_->coursesComboBox->currentIndex())->reviewRequest();
    updateProgressBar(ui_->coursesComboBox->currentIndex());
    LearningWindow dialog(user_->getCourseManager(), user_->getUserStats(), ui_->coursesComboBox->currentIndex(), this);
    dialog.setWindowTitle("SuperMemo");
    if(dialog.exec()) {
        updateWindow();
        //updateProgressBar(ui_->coursesComboBox->currentIndex());
    }
}

void MainMenuWindow::on_activityStatsButton_clicked() {
    ActivityStatisticsWindow dialog(user_->getUserStats(), this);
    dialog.setWindowTitle("Statystyki aktywności użytkownika");
    dialog.exec();
}

void MainMenuWindow::on_actionWarpTime_triggered() {
    for(int i = 0; i < user_->getCourseManager().getCoursesNumber(); i++) {
        user_->getCourseManager().getCourse(i)->simulateTime(-7);
    }
}

void MainMenuWindow::on_exitButton_clicked() {
    QCoreApplication::quit();
}

void MainMenuWindow::on_actionExport_triggered() {
    QString outputFileName = QFileDialog::getSaveFileName(nullptr, "Zapisywanie jako", ".", "Plik tekstowy (*.txt)" );
    std::fstream outputFile;
    outputFile.open(outputFileName.toStdString(), std::ios::trunc | std::ios::out);
    Course *selectedCourse = user_->getCourseManager().getCourse(ui_->coursesComboBox->currentIndex());
    outputFile << selectedCourse->getName().toStdString() << std::endl;
    for(int i = 0; i < selectedCourse->getSizeCardsToRepeat(); i++) {
        Card *card = selectedCourse->getCardToRepeat(i);
        writeObjectsToFile(outputFile, card);
    }
    for(int i = 0; i < selectedCourse->getSizeCardsRepeated(); i++) {
        Card *card = selectedCourse->getCardRepeated(i);
        writeObjectsToFile(outputFile, card);
    }
    outputFile.close();
}

void MainMenuWindow::writeObjectsToFile(std::fstream &file, Card *card) {
    file << card->getQuestion().toStdString()<<";"<<card->getAnswer().toStdString()<<";";
    if(card->getImagePath().isEmpty())
        file<<"-;";
    else file <<
        card->getImagePath().toStdString()<<";";
    if(card->getSoundPath().isEmpty())
        file<<"-;"<<std::endl;
    else
        file << card->getSoundPath().toStdString()<<";"<<std::endl;
}

void MainMenuWindow::on_actionImport_triggered() {
    QString inputFileName = QFileDialog::getOpenFileName(this, "Otwórz plik", "../SuperMemo/example_courses", "Plik tekstowy (*.txt)" );
    std::fstream inputFile;
    inputFile.open(inputFileName.toStdString(), std::ios::in);
    std::string fName;
    QString name;
    getline(inputFile, fName);
    name = QString::fromStdString(fName);
    for(int i = 0; i < user_->getCourseManager().getCoursesNumber(); i++) {
        if(user_->getCourseManager().getCourse(i)->getName() == name) {
            createErrorMessageBox("Kurs o takiej nazwie już istnieje");
            return;
        }
    }
    if(name.isEmpty()) {
        createErrorMessageBox("Plik jest pusty");
        return;
    }
    Course *newCourse = new Course(name);
    std::string question, answer, imagePath, soundPath;
    while(!inputFile.eof()) {
        std::string trash;
        getline(inputFile, question, ';');
        getline(inputFile, answer, ';');
        getline(inputFile, imagePath, ';');
        getline(inputFile, soundPath, ';');
        getline(inputFile, trash);
        if(imagePath == "-") imagePath.clear();
        if(soundPath == "-") soundPath.clear();
        Card *newCard = new Card(QString::fromStdString(question), QString::fromStdString(answer), QString::fromStdString(imagePath), QString::fromStdString(soundPath), QDate::currentDate());
        newCourse->addCardToRepeat(newCard);
        newCourse->incrementCardsCounter();
    }
    user_->getCourseManager().addCourse(newCourse);
    updateWindow();
}

void MainMenuWindow::on_actionDelete_selected_course_triggered() {
    user_->getCourseManager().deleteCourse(ui_->coursesComboBox->currentIndex());
    updateWindow();
}

void MainMenuWindow::createErrorMessageBox(QString text) {
    QMessageBox msg;
    msg.setText(text);
    msg.setStandardButtons(QMessageBox::Apply);
    msg.setDefaultButton(QMessageBox::Apply);
    msg.exec();
}
