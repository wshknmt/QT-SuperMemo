#include "ActivityStatisticsWindow.h"
#include "ui_ActivityStatisticsWindow.h"

ActivityStatisticsWindow::ActivityStatisticsWindow(UserStats &uStats, QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::ActivityStatisticsWindow)
{
    ui_->setupUi(this);
    userStats_ = &uStats;
    createDatesList();

    /*-------------------tylko do testow-------------------------------*/
    LearningDate learningDate;
    learningDate.date = QDate::currentDate().addDays(-2);
    learningDate.counter = 13;
    learningDates_.append(learningDate);

    learningDate.date = QDate::currentDate().addDays(-3);
    learningDate.counter = 7;
    learningDates_.append(learningDate);

    learningDate.date = QDate::currentDate().addDays(-4);
    learningDate.counter = 12;
    learningDates_.append(learningDate);

    learningDate.date = QDate::currentDate().addDays(-5);
    learningDate.counter = 4;
    learningDates_.append(learningDate);
    /*------------------------------------------------------------------*/

    std::sort(learningDates_.begin(), learningDates_.end(), datesComparison);

    QBarSet *set = new QBarSet("aktywność");
    for(int i = 0; i < learningDates_.size(); i++)
        set->append(learningDates_[i].counter);

    QBarSeries *series = new QBarSeries();
    series->append(set);
    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsCenter);


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Aktywność użytkownika w poszczególnych datach");
    QFont font = chart->titleFont();
    font.setPointSize(13);
    chart->setTitleFont(font);
    chart->setAnimationOptions(QChart::AllAnimations);

    QStringList categories;
    for(int i = 0; i < learningDates_.size(); i++) {
        QLocale locale = QLocale(QLocale::Polish, QLocale::Poland);
        QString polishDate = locale.toString(learningDates_[i].date, "d MMM yyyy");
        //categories.append(learningDates_[i].date.toString(Qt::RFC2822Date));
        categories.append(polishDate);
    }


    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui_->horizontalFrame);
    chartView->setMinimumHeight(350);
    chartView->setMinimumWidth(780);
}

ActivityStatisticsWindow::~ActivityStatisticsWindow() {
    delete ui_;
}

bool ActivityStatisticsWindow::areDatesEqual(QDate date1, QDate date2) {
    if(date1.day() == date2.day() && date1.month() == date2.month() && date1.year() == date2.year())
        return true;
    return false;
}

void ActivityStatisticsWindow::createDatesList() {
    for(int i = 0; i < userStats_->getSize(); i++) {
        bool existInList = false;
        for(int j = 0; j < learningDates_.size(); j++) {
            if(areDatesEqual(userStats_->getStat(i).first, learningDates_[j].date)) {
                learningDates_[j].counter++;
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
