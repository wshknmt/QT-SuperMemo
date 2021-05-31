#ifndef USERCALENDARWINDOW_H
#define USERCALENDARWINDOW_H

#include <QDialog>
#include <QTextCharFormat>
#include "CoursesManager.h"

namespace Ui {
class UserCalendarWindow;
}

class UserCalendarWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UserCalendarWindow(CoursesManager &cManager, QWidget *parent = nullptr);
    ~UserCalendarWindow();
    void markDate(QDate date);
    void markDates();
    bool isEqualToCurrentDate(QDate date);
    bool areDatesEqual(QDate date1, QDate date2);

private slots:
    void on_repeatListWidget_itemSelectionChanged();
    void on_userCalendar_selectionChanged();

    void on_repeatButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::UserCalendarWindow *ui_;
    CoursesManager *coursesManager_;
    QTextCharFormat repeatHighlight_;
};

#endif // USERCALENDARWINDOW_H
