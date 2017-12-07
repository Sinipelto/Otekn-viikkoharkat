#-------------------------------------------------
#
# Project created by QtCreator 2014-02-04T14:25:31
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_unittest
CONFIG   += console
CONFIG   -= app_bundle

CONFIG += c++11

TEMPLATE = app


SOURCES += tst_unittest.cc \
    ../DateProject/date.cc
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../DateProject/date.hh

# Added afterwards to find the files
INCLUDEPATH += ../DateProject
DEPENDPATH  += ../DateProject
