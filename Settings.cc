#include "Settings.h"
#include <QMutex>

static QMutex mutexSettings;
Settings* Settings::pInstance_ = nullptr;

Settings::Settings() : isFullScreen_(false)
{
}

Settings& Settings::getInstance()
{
    if(!pInstance_) {
        mutexSettings.lock();
        if(!pInstance_)
            pInstance_ = new Settings();
        mutexSettings.unlock();
    }
    return *pInstance_;
}

bool Settings::isFullScreen()
{
    return isFullScreen_;
}

void Settings::setFullScreen(bool isFullScreen)
{
    isFullScreen_ = isFullScreen;
}
