#include "Settings.h"

Settings* Settings::pInstance_ = nullptr;

Settings::Settings(){

}
Settings* Settings::getInstance() {
    if(!pInstance_)
        pInstance_ = new Settings;
    return pInstance_;
}

bool Settings::isFullScreen() {
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

QFont Settings::getFont() {
    return font_;
}
void Settings::setFont(QFont font) {
    this->font_ = font;
}
