#include <QTextStream>
#include "UserCalendarWindow.h"
#include "ui_UserCalendarWindow.h"
#include "LearningWindow.h"
#include "Settings.h"

UserCalendarWindow::UserCalendarWindow(CoursesManager &cManager, UserStats &uStats, QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::UserCalendarWindow)
{
    ui_->setupUi(this);
    ui_->repeatButton->setEnabled(false);
    coursesManager_ = &cManager;
    userStats_ = &uStats;
    repeatHighlight_.setBackground(QColor(102,255,102));
    markDates();
    /*ui_->repeatListWidget->addItem("Test");
    ui_->repeatListWidget->addItem("Test2");
    ui_->repeatListWidget->addItem("Test3");
    */
    //ui_->repeatListWidget->setEnabled(true);
    ui_->repeatListWidget[0].setEnabled(false);
    //ui_->
}

UserCalendarWindow::~UserCalendarWindow() {
    delete ui_;
}

void UserCalendarWindow::markDate(QDate date) {
    ui_->userCalendar->setDateTextFormat(date, repeatHighlight_);
}

bool UserCalendarWindow::isEqualToCurrentDate(QDate date) {
    QDate current = QDate::currentDate();
    if(current.day() == date.day() && current.month() == date.month() && current.year() == date.year())
        return true;
    return false;
}

bool UserCalendarWindow::areDatesEqual(QDate date1, QDate date2) {
    if(date1.day() == date2.day() && date1.month() == date2.month() && date1.year() == date2.year())
        return true;
    return false;
}

void UserCalendarWindow::markDates() {
    for(int i=0; i < coursesManager_->getCoursesNumber(); i++ ) {
        Course *course = coursesManager_->getCourse(i);
        for(int j = 0; j < course->getSizeCardsToRepeat(); j++) {
            Card *card = course->getCardToRepeat(j);
            if(card->getRepeatDate() < QDate::currentDate())
                markDate(QDate::currentDate());
            else
                markDate(card->getRepeatDate());
        }
        for(int j = 0; j < course->getSizeCardsRepeated(); j++) {
            Card *card = course->getCardRepeated(j);
            if(card->getRepeatDate() < QDate::currentDate())
                markDate(QDate::currentDate());
            else
                markDate(card->getRepeatDate());
        }
    }
}

void UserCalendarWindow::on_repeatListWidget_itemSelectionChanged() {
    if(ui_->repeatListWidget->selectedItems().size() == 1)
        ui_->repeatButton->setEnabled(true);
    else
        ui_->repeatButton->setEnabled(false);
}

void UserCalendarWindow::on_userCalendar_selectionChanged() {
    bool existInListWidget = false;
    ui_->repeatListWidget->clear();
    if(isEqualToCurrentDate(ui_->userCalendar->selectedDate()))
        ui_->repeatListWidget->setEnabled(true);
    else
        ui_->repeatListWidget->setEnabled(false);
    if( isEqualToCurrentDate( ui_->userCalendar->selectedDate()) || ui_->userCalendar->selectedDate() > QDate::currentDate()) {
        for(int i=0; i < coursesManager_->getCoursesNumber(); i++ ) {
            existInListWidget = false;
            Course *course = coursesManager_->getCourse(i);
            for(int j = 0; j < course->getSizeCardsToRepeat(); j++) {
                Card *card = course->getCardToRepeat(j);
                if(areDatesEqual(ui_->userCalendar->selectedDate(), card->getRepeatDate())) {
                    if( ui_->repeatListWidget->findItems(course->getName(), Qt::MatchExactly ).size() >= 1 ) {
                        existInListWidget = true;
                        break;
                    } else {
                        ui_->repeatListWidget->addItem(course->getName());
                        existInListWidget = true;
                        break;
                    }
                } else if(isEqualToCurrentDate(ui_->userCalendar->selectedDate()) && card->getRepeatDate() < QDate::currentDate()) {
                    if( ui_->repeatListWidget->findItems(course->getName(), Qt::MatchExactly ).size() >= 1 ) {
                        existInListWidget = true;
                        break;
                    } else {
                        ui_->repeatListWidget->addItem(course->getName());
                        existInListWidget = true;
                        break;
                    }
                }
            }
            if(existInListWidget)
                continue;
            for(int j = 0; j < course->getSizeCardsRepeated(); j++) {
                Card *card = course->getCardRepeated(j);
                if(areDatesEqual(ui_->userCalendar->selectedDate(), card->getRepeatDate())) {
                    if( ui_->repeatListWidget->findItems(course->getName(), Qt::MatchExactly ).size() >= 1 ) {
                        break;
                    } else {
                        ui_->repeatListWidget->addItem(course->getName());
                        break;
                    }
                } else if(isEqualToCurrentDate(ui_->userCalendar->selectedDate()) && card->getRepeatDate() < QDate::currentDate()) {
                    if( ui_->repeatListWidget->findItems(course->getName(), Qt::MatchExactly ).size() >= 1 ) {
                        break;
                    } else {
                        ui_->repeatListWidget->addItem(course->getName());
                        break;
                    }
                }
            }
        }
    }
    if(ui_->repeatListWidget->count() == 0)
        ui_->repeatListWidget->setEnabled(false);
}

void UserCalendarWindow::on_repeatButton_clicked() {
    QString courseName = ui_->repeatListWidget->selectedItems()[0]->text();
    int index = 0;
    for(int i = 0; i < coursesManager_->getCoursesNumber(); i++) {
        if(courseName == coursesManager_->getCourse(i)->getName()) {
            index = i;
            break;
        }
    }
    LearningWindow dialog(*coursesManager_, *userStats_, index, this);
    dialog.setWindowTitle("SuperMemo");
    if(dialog.exec()) {
        clearCalendar();
        markDates();

    }
}

void UserCalendarWindow::clearCalendar() {
    ui_->userCalendar->setDateTextFormat(QDate() , QTextCharFormat());
}

void UserCalendarWindow::on_closeButton_clicked()
{
    accept();
}
