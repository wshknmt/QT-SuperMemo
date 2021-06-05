/*
 * File name: AcitivityStatisticsWindow.h
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class implementing functions used in activity diagram window.
 */

#ifndef ACTIVITYSTATISTICSWINDOW_H
#define ACTIVITYSTATISTICSWINDOW_H

#include <QDialog>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>

#include "UserStats.h"

namespace Ui {
    class ActivityStatisticsWindow;
}

QT_CHARTS_USE_NAMESPACE

typedef struct learningDate {
    QDate date;
    int counter;
} LearningDate;

class ActivityStatisticsWindow : public QDialog {
    Q_OBJECT

public:
    explicit ActivityStatisticsWindow(UserStats &uStats, QWidget *parent = nullptr);
    ~ActivityStatisticsWindow();
    void createDatesList();
    bool areDatesEqual(QDate date1, QDate date2);

private slots:
    void on_closeButton_clicked();

private:
    static bool datesComparison(const LearningDate &learningDate1, const LearningDate &learningDate2);
    Ui::ActivityStatisticsWindow *ui_;
    QList<LearningDate> learningDates_;
    UserStats *userStats_;
};

#endif // ACTIVITYSTATISTICSWINDOW_H
