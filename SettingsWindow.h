#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QFontDialog>
#include "Settings.h"
namespace Ui {
    class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
   // QFont getFont();

private slots:
    void on_chooseFontButton_clicked();
    void on_closeButton_clicked();
    void on_fullscreenCheckBox_stateChanged(int arg1);

private:
    Ui::SettingsWindow *ui_;
    Settings *settings_;
};

#endif // SETTINGSWINDOW_H
