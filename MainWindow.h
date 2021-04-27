#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NewQuestion.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionNew_question_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    NewQuestion *nq;
};
#endif // MAINWINDOW_H
