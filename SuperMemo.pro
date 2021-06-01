QT       += core gui
QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Card.cc \
    ChangeUserWindow.cc \
    Course.cc \
    CoursesManager.cc \
    LearningWindow.cc \
    MainMenuWindow.cc \
    NewQuestion.cc \
    Settings.cc \
    SettingsWindow.cc \
    StatisticsWindow.cc \
    User.cc \
    UserCalendarWindow.cc \
    UserStats.cc \
    main.cpp

HEADERS += \
    AnswerType.h \
    Card.h \
    ChangeUserWindow.h \
    Course.h \
    CoursesManager.h \
    LearningWindow.h \
    MainMenuWindow.h \
    NewQuestion.h \
    Settings.h \
    SettingsWindow.h \
    StatisticsWindow.h \
    User.h \
    UserCalendarWindow.h \
    UserStats.h

FORMS += \
    ChangeUserWindow.ui \
    LearningWindow.ui \
    MainMenuWindow.ui \
    NewQuestion.ui \
    SettingsWindow.ui \
    StatisticsWindow.ui \
    UserCalendarWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
