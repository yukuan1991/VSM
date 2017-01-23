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
    item/item.cc \
    item/circle.cc \
    item/improve.cc \
    item/reclaimer.cc \
    item/board.cc \
    item/convey.cc \
    item/information.cc \
    item/rectangles.cc \
    item/round.cc \
    item/square.cc \
    item/square_text.cc \
    item/supermarket_rectangles.cc \
    item/three_rectangles.cc \
    item/triangle.cc \
    item/dispatch.cc \
    item/buffer.cc \
    item/communicate.cc \
    item/polygon.cc

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
    item/item.h \
    item/maker.hpp \
    item/circle.h \
    item/improve.h \
    item/reclaimer.h \
    item/board.h \
    item/convey.h \
    item/information.h \
    item/rectangles.h \
    item/round.h \
    item/square.h \
    item/square_text.h \
    item/supermarket_rectangles.h \
    item/three_rectangles.h \
    item/triangle.h \
    item/dispatch.h \
    item/buffer.h \
    item/communicate.h \
    item/polygon.h

FORMS += \
    flow_main.ui \
    remark_widget.ui

