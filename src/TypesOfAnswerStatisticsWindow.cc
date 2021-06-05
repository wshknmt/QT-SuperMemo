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

    QPieSeries *series = new QPieSeries();

    series->append("Poprawna odpowiedź", userStats_->getGoodCounter());
    series->append("Prawie \npoprawna \nodpowiedź", userStats_->getMixedCounter());
    series->append("Niepoprawna odpowiedź", userStats_->getWrongCounter());

    series->setLabelsVisible(true);
    series->setLabelsPosition(QPieSlice::LabelOutside);

    QPieSlice *gSlice = series->slices().at(0);
    gSlice->setBrush(Qt::green);
    QPieSlice *mSlice = series->slices().at(1);
    mSlice->setBrush(Qt::yellow);
    QPieSlice *wSlice = series->slices().at(2);
    wSlice->setBrush(Qt::red);

    QPalette palette;
    palette.setColor(QPalette::WindowText, QColor(50, 205, 50));
    ui_->label1->setPalette(palette);
    palette.setColor(QPalette::WindowText, QColor(235, 188, 78));
    ui_->label2->setPalette(palette);
    palette.setColor(QPalette::WindowText, Qt::red);
    ui_->label3->setPalette(palette);

    ui_->label1->setText(QString("%1%").arg(100*gSlice->percentage(), 0, 'f', 1) + " poprawnych odpowiedzi");
    ui_->label2->setText(QString("%1%").arg(100*mSlice->percentage(), 0, 'f', 1) + " prawie poprawnych odpowiedzi");
    ui_->label3->setText(QString("%1%").arg(100*wSlice->percentage(), 0, 'f', 1) + " niepoprawnych odpowiedzi");

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Wykres poprawności udzielanych odpowiedzi");
    QFont font = chart->titleFont();
    font.setPointSize(13);
    chart->setTitleFont(font);
    chart->setAnimationOptions(QChart::AllAnimations);

    if(userStats_->getSize() != 0) {
        QChartView *chartview = new QChartView(chart);
        chartview->setParent(ui_->horizontalFrame);
    }
}

TypesOfAnswerStatisticsWindow::~TypesOfAnswerStatisticsWindow() {
    delete ui_;
}

void TypesOfAnswerStatisticsWindow::on_closeButton_clicked() {
    accept();
}
