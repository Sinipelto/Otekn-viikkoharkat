#-------------------------------------------------
#
# Project created by QtCreator 2014-02-04T14:25:31
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_yksikkotesti
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_yksikkotesti.cc \
    ../PaivaysProjekti/paivays.cc
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../PaivaysProjekti/paivays.hh

# Lisätty jälkeenpäin tiedostojen löytämiseksi
INCLUDEPATH += ../PaivaysProjekti
DEPENDPATH  += ../PaivaysProjekti
