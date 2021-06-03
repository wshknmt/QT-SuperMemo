#ifndef SETTINGS_H
#define SETTINGS_H
#include <QWidget>

class Settings {
public:
    static Settings* getInstance();
    bool isFullScreen();
    void setParent(QWidget *parent);
    void enableFullScreen();
    void disableFullScreen();
    QFont getFont();
    void setFont(QFont font);

private:
    Settings();
    static Settings* pInstance_;
    bool isFullScreen_ = false;
    QWidget *parent_;
    QFont font_;
};

#endif // SETTINGS_H
