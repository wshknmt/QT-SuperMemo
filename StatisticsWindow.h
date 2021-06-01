#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QDialog>
#include <QtCharts>
#include <QPieSeries>
#include <QChartView>
#include "UserStats.h"

namespace Ui {
class StatisticsWindow;
}

class StatisticsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsWindow(UserStats &uStats, QWidget *parent = nullptr);
    ~StatisticsWindow();

private:
    Ui::StatisticsWindow *ui_;
    UserStats *userStats_;
};

#endif // STATISTICSWINDOW_H
