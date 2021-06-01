#include "StatisticsWindow.h"
#include "ui_StatisticsWindow.h"

StatisticsWindow::StatisticsWindow(UserStats &uStats, QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::StatisticsWindow)
{
    ui_->setupUi(this);
    userStats_ = &uStats;
    userStats_->updateCounters();

    QPieSeries *series = new QPieSeries();

    series->append("Poprawna odpowiedź", userStats_->getGoodCounter());
    series->append("Prawie poprawna odpowiedź", userStats_->getMixedCounter());
    series->append("Niepoprawna odpowiedź", userStats_->getWrongCounter());

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Wykres poprawności udzielanych odpowiedzi");

    QChartView *chartview = new QChartView(chart);
    chartview->setParent(ui_->horizontalFrame);
}

StatisticsWindow::~StatisticsWindow()
{
    delete ui_;
}
