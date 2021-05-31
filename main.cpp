#include <iostream>
#include <QApplication>
#include "MainMenuWindow.h"
using namespace std;
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainMenuWindow w;
    w.setWindowTitle("Menu główne");
    w.setWindowIcon(QIcon(":/images/Icons/Supermemo-icon.png"));
    w.show();
    return a.exec();
}
