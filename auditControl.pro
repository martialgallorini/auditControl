#-------------------------------------------------
#
# Project created by QtCreator 2013-07-27T11:12:52
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = auditControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcpclient.cpp \
    matrix.cpp \
    projector.cpp \
    pulse.cpp \
    vp771.cpp

HEADERS  += mainwindow.h \
    tcpclient.h \
    matrix.h \
    projector.h \
    pulse.h \
    vp771.h

FORMS    += mainwindow.ui \
    matrix.ui \
    projector.ui \
    pulse.ui \
    vp771.ui

RESOURCES += \
    ressources.qrc
