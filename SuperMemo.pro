QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Card.cpp \
    Course.cpp \
    LearningWindow.cpp \
    MainMenuWindow.cpp \
    NewQuestion.cpp \
    User.cpp \
    main.cpp

HEADERS += \
    Card.h \
    Course.h \
    LearningWindow.h \
    MainMenuWindow.h \
    NewQuestion.h \
    User.h

FORMS += \
    LearningWindow.ui \
    MainMenuWindow.ui \
    NewQuestion.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
