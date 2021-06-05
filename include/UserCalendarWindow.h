/*
 * File name: UserCalendarWindow.h
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class implementing functions for user calendar window.
 */

#ifndef USERCALENDARWINDOW_H
#define USERCALENDARWINDOW_H

#include <QDialog>
#include <QTextCharFormat>

#include "CoursesManager.h"
#include "UserStats.h"

namespace Ui {
class UserCalendarWindow;
}

class UserCalendarWindow : public QDialog {
    Q_OBJECT

public:
    explicit UserCalendarWindow(CoursesManager &cManager, UserStats &uStats, QWidget *parent = nullptr);
    ~UserCalendarWindow();
    void markDate(QDate date);
    void markDates();
    bool isEqualToCurrentDate(QDate date) const;
    bool areDatesEqual(QDate date1, QDate date2) const;
    void clearCalendar();

private slots:
    void on_repeatListWidget_itemSelectionChanged();
    void on_userCalendar_selectionChanged();
    void on_repeatButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::UserCalendarWindow *ui_;
    CoursesManager *coursesManager_;
    UserStats *userStats_;
    QTextCharFormat repeatHighlight_;
};

#endif // USERCALENDARWINDOW_H
