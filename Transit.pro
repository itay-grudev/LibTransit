#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T13:17:23
#
#-------------------------------------------------

QT       -= core gui

TARGET = Transit
TEMPLATE = lib
CONFIG += staticlib

# Should be changed according boost location
win32:INCLUDEPATH += "C:/Program Files/boost/boost_1_54_0" # System specific!

# Why not use the latest and gratest version of C++
CONFIG += c++11 # Required for some C++ 11 functionality

SOURCES += transit.cpp \
    transitprivate.cpp \
    transitparams.cpp

HEADERS += transit.h \
    transitprivate.h \
    transitparams.h \
    darekninglaw.h \
    transit_global.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
