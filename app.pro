QT += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11

VPATH += src \
    include \
    forms \
    resources

HEADERS += \
    ActivityStatisticsWindow.h \
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
    TypesOfAnswerStatisticsWindow.h \
    User.h \
    UserCalendarWindow.h \
    UserStats.h
    
SOURCES += \
    ActivityStatisticsWindow.cc \
    Card.cc \
    ChangeUserWindow.cc \
    Course.cc \
    CoursesManager.cc \
    LearningWindow.cc \
    MainMenuWindow.cc \
    NewQuestion.cc \
    Settings.cc \
    SettingsWindow.cc \
    TypesOfAnswerStatisticsWindow.cc \
    User.cc \
    UserCalendarWindow.cc \
    UserStats.cc \
    main.cc

FORMS += \
    ActivityStatisticsWindow.ui \
    ChangeUserWindow.ui \
    LearningWindow.ui \
    MainMenuWindow.ui \
    NewQuestion.ui \
    SettingsWindow.ui \
    TypesOfAnswerStatisticsWindow.ui \
    UserCalendarWindow.ui

RESOURCES += \
    resources.qrc

INCLUDEPATH += include
DESTDIR = bin
RCC_DIR = build
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build

test.target = test
test.commands = cd tests && qmake && make && ./tests
QMAKE_EXTRA_TARGETS += test

extraclean.commands = rm -f -r build/* bin/* && rm -f .qmake.stash tests/.qmake.stash tests/tests tests/Makefile
clean.depends = extraclean
QMAKE_EXTRA_TARGETS += extraclean clean

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
