#include "MainMenuWindow.h"
#include <iostream>
#include <QApplication>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenuWindow w;
    w.setWindowTitle("Main Menu");
    w.setWindowIcon(QIcon(":/images/Icons/Supermemo-icon.png"));
    w.show();
    return a.exec();
}
