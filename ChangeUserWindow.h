#ifndef CHANGEUSERWINDOW_H
#define CHANGEUSERWINDOW_H

#include <QDialog>
#include "User.h"

namespace Ui {
    class ChangeUserWindow;
}

class ChangeUserWindow : public QDialog {
    Q_OBJECT

public:
    explicit ChangeUserWindow(QList <User*> &usersList, QWidget *parent = nullptr);
    ~ChangeUserWindow();
    User* getCurrentUser();

private slots:
    void on_nameTextEdit_textChanged();
    void on_cancelButton_clicked();
    void on_createButton_clicked();
    void on_chooseButton_clicked();

private:
    Ui::ChangeUserWindow *ui_;
    User *current_user_;
    QList <User*> *users_;
};

#endif // CHANGEUSERWINDOW_H
