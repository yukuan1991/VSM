#-------------------------------------------------
#
# Project created by QtCreator 2016-08-24T21:41:48
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vsm
TEMPLATE = app

include (../Shionto.pri)
include (../3rd-party/3rd-party.pri)
include (../utility/utility.pri)
include (../qt-tools/qt-tools.pri)

DEFINES += UPDATE_FILE_PATH=\\\"software/flow-app\\\"
DEFINES += SOFTWARE_NAME=\\\"flow-app\\\"
DEFINES += SVG_DIR=\\\"svg\\\"
DEFINES += SERVER_ADDR=\\\"116.62.10.199\\\"
DEFINES += UPDATE_PATH=\\\"update/update\\\"
DEFINES += EXEC_FILE=\\\"$$TARGET\\\"

SOURCES += \
    flow_app.cc \
    canvas_scene.cc \
    canvas_view.cc \
    drawer_list.cc \
    flow_main.cpp \
    canvas_body.cc \
    flow_utility.cc \
    remark_widget.cpp

HEADERS += \
    flow_app.h \
    canvas_scene.h \
    canvas_view.h \
    drawer_list.h \
    defs.hpp \
    flow_main.h \
    canvas_body.h \
    flow_utility.h \
    remark_widget.h

FORMS += \
    flow_main.ui \
    remark_widget.ui

