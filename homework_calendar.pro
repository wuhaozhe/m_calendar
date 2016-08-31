#-------------------------------------------------
#
# Project created by QtCreator 2016-08-24T09:14:46
#
#-------------------------------------------------

QT       += core gui
TRANSLATIONS += cn.ts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = homework_calendar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    core.cpp \
    basicwidget.cpp \
    basiccalendar.cpp \
    week.cpp \
    smallwindow.cpp \
    all_message.cpp \
    event.cpp \
    widget_message.cpp \
    in_config.cpp \
    startwindow.cpp \
    projectlistwidget.cpp \
    global.cpp

HEADERS  += mainwindow.h \
    core.h \
    basicwidget.h \
    basiccalendar.h \
    week.h \
    smallwindow.h \
    all_message.h \
    event.h \
    widget_message.h \
    in_config.h \
    startwindow.h \
    projectlistwidget.h \
    global.h

FORMS    += mainwindow.ui \
    smallwindow.ui \
    startwindow.ui

RESOURCES +=
