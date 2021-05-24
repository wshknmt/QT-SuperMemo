#ifndef USERCALENDARWINDOW_H
#define USERCALENDARWINDOW_H

#include <QDialog>

namespace Ui {
    class UserCalendarWindow;
}

class UserCalendarWindow : public QDialog{
    Q_OBJECT

public:
    explicit UserCalendarWindow(QWidget *parent = nullptr);
    ~UserCalendarWindow();

private:
    Ui::UserCalendarWindow *ui;
};

#endif // USERCALENDARWINDOW_H
