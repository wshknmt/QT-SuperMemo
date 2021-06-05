/*
 * File name: Settings.h
 * Author: Michał Kopyt, Paweł Martyniuk
 * Project: Learning app
 * Description: Singleton class representing app settings.
 */

#include "Settings.h"

Settings* Settings::pInstance_ = nullptr;

Settings::Settings(bool isFullScreen) : isFullScreen_(isFullScreen) {}

Settings* Settings::getInstance() {
    if(!pInstance_)
        pInstance_ = new Settings(false);
    return pInstance_;
}

bool Settings::isFullScreen() const {
    return isFullScreen_;
}

void Settings::enableFullScreen() {
    parent_->setWindowState(Qt::WindowFullScreen);
    isFullScreen_ = true;
}
void Settings::disableFullScreen() {
    parent_->setWindowState(Qt::WindowNoState);
    isFullScreen_ = false;
}

void Settings::setParent(QWidget *parent) {
    this->parent_ = parent;
}

QFont Settings::getFont() const {
    return font_;
}
void Settings::setFont(QFont font) {
    this->font_ = font;
}
