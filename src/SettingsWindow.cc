/*
 * File name: SettingsWindow.cc
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Class implementing functions for settings window.
 */

#include "SettingsWindow.h"
#include "ui_SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent), ui_(new Ui::SettingsWindow)
{
    ui_->setupUi(this);
    Settings::getInstance()->setParent(parent);
    if(Settings::getInstance()->isFullScreen())
        ui_->fullscreenCheckBox->setChecked(true);
}

SettingsWindow::~SettingsWindow() {
    delete ui_;
}

void SettingsWindow::on_chooseFontButton_clicked() {
    bool ok;
    Settings::getInstance()->setFont(QFontDialog::getFont(&ok, QFont( "Comic Sans MS", 8 ),this,tr("Wybierz czcionkę") ));
}

void SettingsWindow::on_closeButton_clicked() {
    accept();
}

void SettingsWindow::on_fullscreenCheckBox_stateChanged(int arg1) {
    if(arg1 == 2)
        Settings::getInstance()->enableFullScreen();
    else if(arg1 == 0)
        Settings::getInstance()->disableFullScreen();
}
