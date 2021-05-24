#ifndef SETTINGS_H
#define SETTINGS_H

class Settings {
public:
    static Settings& getInstance();
    bool isFullScreen();
    void setFullScreen(bool isFullScreen);

private:
    Settings();
    static Settings* pInstance_;
    bool isFullScreen_;
};

#endif // SETTINGS_H
