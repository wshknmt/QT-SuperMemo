/*
 * File name: ChangeUserWindow.cc
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class implementing functions for user change window.
 */

#include <QTextStream>

#include "ChangeUserWindow.h"
#include "ui_ChangeUserWindow.h"

ChangeUserWindow::ChangeUserWindow(QList<User*> &usersList, QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::ChangeUserWindow)
{
    ui_->setupUi(this);
    ui_->nameTextEdit->clear();
    ui_->createButton->setEnabled(false);
    ui_->usersComboBox->clear();
    ui_->usersComboBox->setEnabled(false);
    ui_->chooseButton->setEnabled(false);
    users_ = &usersList;
    if(usersList.size() == 1) {
        ui_->usersComboBox->addItem(usersList[0]->getName());
    } else if(usersList.size() > 1) {
        ui_->usersComboBox->setEnabled(true);
        ui_->chooseButton->setEnabled(true);
        for(int i = 0; i < usersList.size(); ++i) {
            ui_->usersComboBox->addItem(usersList[i]->getName());
        }
    }
}

ChangeUserWindow::~ChangeUserWindow() {
    delete ui_;
}

User* ChangeUserWindow::getCurrentUser() const {
    return current_user_;
}

void ChangeUserWindow::on_nameTextEdit_textChanged() {
    if(ui_->nameTextEdit->toPlainText().isEmpty())
        ui_->createButton->setEnabled(false);
    else
        ui_->createButton->setEnabled(true);
}

void ChangeUserWindow::on_cancelButton_clicked() {
    reject();
}

void ChangeUserWindow::on_createButton_clicked() {
    current_user_ = new User(ui_->nameTextEdit->toPlainText());
    (*users_).append(current_user_);
    accept();
}

void ChangeUserWindow::on_chooseButton_clicked() {
    current_user_ = (*users_)[ui_->usersComboBox->currentIndex()];
    accept();
}
