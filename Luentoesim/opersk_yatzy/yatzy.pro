#-------------------------------------------------
#
# Project created by QtCreator 2014-11-30T14:46:49
#
#-------------------------------------------------
CONFIG   += c++11

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = yatzy
TEMPLATE = app


SOURCES += main.cpp\
        paaikkuna.cpp \
    apufunktiot.cpp

HEADERS  += paaikkuna.hh \
    apufunktiot.hh

FORMS    += paaikkuna.ui

RESOURCES += \
    nopparesurssi.qrc
