#include "SettingsWindow.h"
#include "ui_SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::SettingsWindow)
{
    ui_->setupUi(this);
    settings_ = settings_->getInstance();
    settings_->setParent(parent);
    if(settings_->isFullScreen())
        ui_->fullscreenCheckBox->setChecked(true);
}

SettingsWindow::~SettingsWindow() {
    delete ui_;
}

void SettingsWindow::on_chooseFontButton_clicked() {
    bool ok;
    settings_->setFont(QFontDialog::getFont(&ok, QFont( "Comic Sans MS", 8 ),this,tr("Wybierz czcionkę") ));
}

/*QFont SettingsWindow::getFont() {
    return settings_->getFont();
}*/

void SettingsWindow::on_closeButton_clicked() {
    accept();
}

void SettingsWindow::on_fullscreenCheckBox_stateChanged(int arg1) {
    if(arg1 == 2)
        settings_->enableFullScreen();
    else if(arg1 == 0)
       settings_->disableFullScreen();
}
