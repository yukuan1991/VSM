#-------------------------------------------------
#
# Project created by QtCreator 2016-08-24T21:41:48
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = flow-chart
TEMPLATE = app

include (../Shionto.pri)
include (../3rd-party/3rd-party.pri)
include (../utility/utility.pri)
include (../qt-tools/qt-tools.pri)

SOURCES += \
    flow_app.cc \
    canvas_scene.cc \
    canvas_view.cc \
    drawer_list.cc \
    flow_main.cpp \
    canvas_body.cc \
    flow_utility.cc

HEADERS += \
    flow_app.h \
    canvas_scene.h \
    canvas_view.h \
    drawer_list.h \
    defs.hpp \
    flow_main.h \
    canvas_body.h \
    flow_utility.h

FORMS += \
    flow_main.ui

