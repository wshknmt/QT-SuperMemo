TEMPLATE = app
CONFIG -= app_bundle
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += core gui widgets multimedia

isEmpty(BOOST_INCLUDE_DIR): BOOST_INCLUDE_DIR=$$(BOOST_INCLUDE_DIR)
!isEmpty(BOOST_INCLUDE_DIR): INCLUDEPATH *= $${BOOST_INCLUDE_DIR}

isEmpty(BOOST_INCLUDE_DIR): {
    message("BOOST_INCLUDE_DIR is not set, assuming Boost can be found automatically in your system")
}

VPATH += ../src \
    ../include \
    ../forms \
    ../resources

HEADERS += \
    CoursesManager.h \
    Course.h \
    Card.h
    
SOURCES += \
    supermemoSuite.cc \
    CoursesManager.cc \
    Course.cc \
    Card.cc

INCLUDEPATH = ../include
RCC_DIR = ../build
OBJECTS_DIR = ../build
MOC_DIR = ../build
UI_DIR = ../build
