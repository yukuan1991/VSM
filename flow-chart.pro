#-------------------------------------------------
#
# Project created by QtCreator 2016-08-24T21:41:48
#
#-------------------------------------------------

QT       += core gui svg opengl

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
DEFINES += ENTITY_DIR=\\\"entity\\\"
DEFINES += MATERIAL_FLOW_DIR=\\\"material_flow\\\"
DEFINES += INFO_FLOW_DIR=\\\"info_flow\\\"
DEFINES += SERVER_ADDR=\\\"116.62.10.199\\\"
DEFINES += UPDATE_PATH=\\\"update/update\\\"
DEFINES += EXEC_FILE=\\\"$$TARGET\\\"

SOURCES += \
    flow_app.cc \
    flow_utility.cc \
    flow_main.cc \
    remark_widget.cc \
    drawer/list.cc \
    drawer/toolbox.cc \
    drawer/info_flow.cc \
    canvas/body.cc \
    canvas/scene.cc \
    canvas/view.cc \
    item/item.cc

HEADERS += \
    flow_app.h \
    defs.hpp \
    flow_main.h \
    flow_utility.h \
    remark_widget.h \
    drawer/list.h \
    drawer/toolbox.h \
    drawer/info_flow.h \
    canvas/body.h \
    canvas/scene.h \
    canvas/view.h \
    item/item.h

FORMS += \
    flow_main.ui \
    remark_widget.ui

