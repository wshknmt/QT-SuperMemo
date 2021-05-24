QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Card.cpp \
    CardUserStats.cc \
    ChangeUserWindow.cpp \
    Course.cpp \
    CourseProgress.cc \
    LearningWindow.cpp \
    MainMenuWindow.cpp \
    NewQuestion.cpp \
    Settings.cc \
    SettingsWindow.cpp \
    User.cpp \
    UserCalendar.cc \
    UserCalendarWindow.cc \
    main.cpp

HEADERS += \
    AnswerType.h \
    Card.h \
    CardUserStats.h \
    ChangeUserWindow.h \
    Course.h \
    CourseProgress.h \
    LearningWindow.h \
    MainMenuWindow.h \
    NewQuestion.h \
    Settings.h \
    SettingsWindow.h \
    User.h \
    UserCalendar.h \
    UserCalendarWindow.h

FORMS += \
    ChangeUserWindow.ui \
    LearningWindow.ui \
    MainMenuWindow.ui \
    NewQuestion.ui \
    SettingsWindow.ui \
    UserCalendarWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
