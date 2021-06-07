/*
 * File name: AcitivityStatisticsWindow.cc
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class implementing functions used in activity diagram window.
 */

#include "ActivityStatisticsWindow.h"
#include "ui_ActivityStatisticsWindow.h"

ActivityStatisticsWindow::ActivityStatisticsWindow(UserStats &uStats, QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::ActivityStatisticsWindow)
{
    ui_->setupUi(this);
    userStats_ = &uStats;
    createDatesList();

    std::sort(learningDates_.begin(), learningDates_.end(), datesComparison);

    set_ = new QBarSet("aktywność");
    for(int i = 0; i < learningDates_.size(); ++i)
        set_->append(learningDates_[i].counter);

    series_ = new QBarSeries();
    series_->append(set_);
    series_->setLabelsVisible(true);
    series_->setLabelsPosition(QAbstractBarSeries::LabelsCenter);

    chart_ = new QChart();
    chart_->addSeries(series_);
    chart_->setTitle("Aktywność użytkownika w poszczególnych datach");
    QFont font = chart_->titleFont();
    font.setPointSize(13);
    chart_->setTitleFont(font);
    chart_->setAnimationOptions(QChart::AllAnimations);

    QStringList categories;
    for(int i = 0; i < learningDates_.size(); ++i) {
        QLocale locale = QLocale(QLocale::Polish, QLocale::Poland);
        QString polishDate = locale.toString(learningDates_[i].date, "d MMM yyyy");
        //categories.append(learningDates_[i].date.toString(Qt::RFC2822Date));
        categories.append(polishDate);
    }


    axis_ = new QBarCategoryAxis();
    axis_->append(categories);
    chart_->createDefaultAxes();
    chart_->setAxisX(axis_, series_);
    chart_->legend()->setVisible(true);
    chart_->legend()->setAlignment(Qt::AlignBottom);

    chartView_ = new QChartView(chart_);
    chartView_->setRenderHint(QPainter::Antialiasing);
    chartView_->setParent(ui_->horizontalFrame);
    chartView_->setMinimumHeight(350);
    chartView_->setMinimumWidth(780);
}

ActivityStatisticsWindow::~ActivityStatisticsWindow() {
    delete chartView_;
    delete ui_;
}

bool ActivityStatisticsWindow::areDatesEqual(QDate date1, QDate date2) {
    if(date1.day() == date2.day() && date1.month() == date2.month() && date1.year() == date2.year())
        return true;
    return false;
}

void ActivityStatisticsWindow::createDatesList() {
    for(int i = 0; i < userStats_->getSize(); ++i) {
        bool existInList = false;
        for(int j = 0; j < learningDates_.size(); ++j) {
            if(areDatesEqual(userStats_->getStat(i).first, learningDates_[j].date)) {
                ++learningDates_[j].counter;
                existInList = true;
                break;
            }
        }
        if(!existInList) {
            LearningDate learningDate;
            learningDate.date = userStats_->getStat(i).first;
            learningDate.counter = 0;
            learningDates_.append(learningDate);
        }
    }
}

void ActivityStatisticsWindow::on_closeButton_clicked() {
    accept();
}

bool ActivityStatisticsWindow::datesComparison(const LearningDate &learningDate1, const LearningDate &learningDate2) {

    if(learningDate1.date.year() < learningDate2.date.year()) return true;
    else if(learningDate1.date.year() == learningDate2.date.year() && learningDate1.date.month() < learningDate2.date.month()) return true;
    else if(learningDate1.date.year() == learningDate2.date.year() && learningDate1.date.month() == learningDate2.date.month() &&
            learningDate1.date.day() < learningDate2.date.day()) return true;
    return false;
}
