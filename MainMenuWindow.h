#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>
#include "Card.h"
#include "Course.h"
#include "MainWindow.h"

namespace Ui {
class MainMenuWindow;
}

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenuWindow(QWidget *parent = nullptr);
    ~MainMenuWindow();

private slots:
    void on_actionNew_course_triggered();

private:
    Ui::MainMenuWindow *ui;
    QList <Course*> coursesList;
};

#endif // MAINMENUWINDOW_H
