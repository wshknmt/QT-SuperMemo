#include "SettingsWindow.h"
#include "ui_SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    this->parent = parent;
    if(parent->windowState() == Qt::WindowFullScreen)
        ui->fullscreenCheckBox->setChecked(true);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}


void SettingsWindow::on_chooseFontButton_clicked()
{
    bool ok;
    font = QFontDialog::getFont(&ok, QFont( "MS Shell Dlg 2", 8 ),this,tr("Pick a font") );
}

QFont SettingsWindow::getFont()
{
    return font;
}

void SettingsWindow::on_closeButton_clicked()
{
    accept();
}

void SettingsWindow::on_fullscreenCheckBox_stateChanged(int arg1)
{
    if(arg1 == 2)
        parent->setWindowState(Qt::WindowFullScreen);
    else if(arg1 == 0)
        parent->setWindowState(Qt::WindowNoState);
}
