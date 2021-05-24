#include "Settings.h"
#include <QMutex>

static QMutex mutex;
Settings* Settings::pInstance_ = nullptr;

Settings::Settings() : isFullScreen_(false)
{
}

Settings& Settings::getInstance()
{
    if(!pInstance_) {
        mutex.lock();
        if(!pInstance_)
            pInstance_ = new Settings();
        mutex.unlock();
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
