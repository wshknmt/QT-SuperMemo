/*
 * File name: TypesOfAnswerStatisticsWindow.cc
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class implementing functions for answers statistics diagram window.
 */

#include "TypesOfAnswerStatisticsWindow.h"
#include "ui_TypesOfAnswerStatisticsWindow.h"

TypesOfAnswerStatisticsWindow::TypesOfAnswerStatisticsWindow(UserStats &uStats, QWidget *parent) :
    QDialog(parent), ui_(new Ui::TypesOfAnswerStatisticsWindow), userStats_(&uStats)
{
    ui_->setupUi(this);
    userStats_->updateCounters();

    series_ = new QPieSeries();

    series_->append("Poprawna odp.", userStats_->getGoodCounter());
    series_->append("Prawie \npoprawna \nodp.", userStats_->getMixedCounter());
    series_->append("Niepoprawna odp.", userStats_->getWrongCounter());

    series_->setLabelsVisible(true);
    series_->setLabelsPosition(QPieSlice::LabelOutside);

    QPieSlice *gSlice = series_->slices().at(0);
    gSlice->setBrush(Qt::green);
    QPieSlice *mSlice = series_->slices().at(1);
    mSlice->setBrush(Qt::yellow);
    QPieSlice *wSlice = series_->slices().at(2);
    wSlice->setBrush(Qt::red);

    QPalette palette;
    palette.setColor(QPalette::WindowText, QColor(50, 205, 50));
    ui_->label1->setPalette(palette);
    palette.setColor(QPalette::WindowText, QColor(235, 188, 78));
    ui_->label2->setPalette(palette);
    palette.setColor(QPalette::WindowText, Qt::red);
    ui_->label3->setPalette(palette);

    ui_->label1->setText(QString("%1%").arg(100*gSlice->percentage(), 0, 'f', 1) + " poprawnych odp.");
    ui_->label2->setText(QString("%1%").arg(100*mSlice->percentage(), 0, 'f', 1) + " prawie poprawnych odp.");
    ui_->label3->setText(QString("%1%").arg(100*wSlice->percentage(), 0, 'f', 1) + " niepoprawnych odp.");

    chart_ = new QChart();
    chart_->addSeries(series_);
    chart_->setTitle("Wykres poprawności udzielanych odpowiedzi");
    QFont font = chart_->titleFont();
    font.setPointSize(13);
    chart_->setTitleFont(font);
    chart_->setAnimationOptions(QChart::AllAnimations);

    if(userStats_->getSize() != 0) {
        chartview_ = new QChartView(chart_);
        chartview_->setParent(ui_->horizontalFrame);
    }
}

TypesOfAnswerStatisticsWindow::~TypesOfAnswerStatisticsWindow() {
    if(userStats_->getSize() != 0) {
        delete chartview_;
    }
    delete ui_;
}

void TypesOfAnswerStatisticsWindow::on_closeButton_clicked() {
    accept();
}
