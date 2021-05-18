#include "ChangeUserWindow.h"
#include "ui_ChangeUserWindow.h"

ChangeUserWindow::ChangeUserWindow(QList <User*> &usersList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeUserWindow)
{
    ui->setupUi(this);
    ui->nameTextEdit->clear();
    ui->createButton->setEnabled(false);
    ui->usersComboBox->clear();
    ui->usersComboBox->setEnabled(false);
    ui->chooseButton->setEnabled(false);
    users = &usersList;
    if(usersList.size() == 1)
    {
        ui->usersComboBox->addItem(usersList[0]->getName());
    }
    else if(usersList.size() > 1)
    {
        ui->usersComboBox->setEnabled(true);
        ui->chooseButton->setEnabled(true);
        for(int i = 0; i < usersList.size(); i++)
        {
            ui->usersComboBox->addItem(usersList[i]->getName());
        }
    }

}

ChangeUserWindow::~ChangeUserWindow()
{
    delete ui;
}

User* ChangeUserWindow::getCurrentUser()
{
    return current_user;
}

void ChangeUserWindow::on_nameTextEdit_textChanged()
{
    if(ui->nameTextEdit->toPlainText().isEmpty())
        ui->createButton->setEnabled(false);
    else
        ui->createButton->setEnabled(true);
}

void ChangeUserWindow::on_cancelButton_clicked()
{
    reject();
}

void ChangeUserWindow::on_createButton_clicked()
{
    current_user = new User(ui->nameTextEdit->toPlainText());
    (*users).append(current_user);
    accept();
}

void ChangeUserWindow::on_chooseButton_clicked()
{
    current_user = (*users)[ui->usersComboBox->currentIndex()];
    accept();
}
