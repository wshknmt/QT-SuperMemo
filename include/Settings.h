/*
 * File name: Settings.h
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Singleton class representing app settings.
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

class Settings {
public:
    static Settings* getInstance();
    bool isFullScreen() const;
    void setParent(QWidget *parent);
    void enableFullScreen();
    void disableFullScreen();
    QFont getFont() const;
    void setFont(QFont font);

private:
    Settings(bool isFullScreen);
    static Settings* pInstance_;
    bool isFullScreen_;
    QWidget *parent_;
    QFont font_;
};

#endif // SETTINGS_H
