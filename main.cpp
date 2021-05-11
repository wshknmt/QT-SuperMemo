#include "MainWindow.h"
#include "MainMenuWindow.h"
#include <iostream>
#include <QApplication>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenuWindow w;
    w.setWindowTitle("SuperMemo");
    w.setWindowIcon(QIcon(":/images/Icons/Supermemo-icon.png"));
    w.show();
    //w.setDefaultImage();
    return a.exec();
}
