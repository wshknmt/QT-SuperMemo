/*
 * File name: main.cc
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Main function of the app.
 */

#include <iostream>
#include <QApplication>
#include <QFont>

#include "MainMenuWindow.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainMenuWindow w;
    QFont f("Ubuntu", 10);
    QApplication::setFont(f);
    w.setWindowTitle("Kopyt & Martyniuk SuperMemo");
    w.setWindowIcon(QIcon(":/images/Icons/Supermemo-icon.png"));
    w.show();
    return a.exec();
}
