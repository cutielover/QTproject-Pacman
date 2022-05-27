#-------------------------------------------------
#
# Project created by QtCreator 2022-05-26T03:38:50
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

CONFIG += c++11 resources_big

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled11
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    config.cpp \
    map.cpp \
    bobject.cpp

HEADERS  += mainwindow.h \
    config.h \
    map.h \
    bobject.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    res.qrc
