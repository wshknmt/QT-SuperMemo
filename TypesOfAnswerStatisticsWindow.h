#ifndef TYPESOFANSWERSTATISTICSWINDOW_H
#define TYPESOFANSWERSTATISTICSWINDOW_H

#include <QDialog>
#include <QtCharts>
#include <QPieSeries>
#include <QChartView>
#include <QPieSlice>
#include "UserStats.h"

namespace Ui {
    class TypesOfAnswerStatisticsWindow;
}

class TypesOfAnswerStatisticsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TypesOfAnswerStatisticsWindow(UserStats &uStats, QWidget *parent = nullptr);
    ~TypesOfAnswerStatisticsWindow();

private slots:
    void on_closeButton_clicked();

private:
    Ui::TypesOfAnswerStatisticsWindow *ui_;
    UserStats *userStats_;
};

#endif // TYPESOFANSWERSTATISTICSWINDOW_H
