#include "UserCalendarWindow.h"
#include "ui_UserCalendarWindow.h"

UserCalendarWindow::UserCalendarWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserCalendarWindow)
{
    ui->setupUi(this);
}

UserCalendarWindow::~UserCalendarWindow()
{
    delete ui;
}
