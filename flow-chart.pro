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
    flow_main.cc \
    drawer/toolbox.cc \
    drawer/info_flow.cc \
    canvas/body.cc \
    canvas/scene.cc \
    canvas/view.cc \
    item/item.cc \
    item/material_flow.cc \
    item/traditional_info_flow.cc \
    item/electric_info_flow.cc \
    drawer/drag_widget.cc \
    item/board_station.cc \
    drawer/drag_pixmap.cc \
    item/cache_or_safe_storage.cc \
    item/fetch_material.cc \
    item/signal_board.cc \
    item/sequence_pull_ball.cc \
    item/balanced_production.cc \
    item/operating_personnel.cc \
    item/board_arrival.cc \
    item/production_sequence.cc \
    attribute_widget.cc \
    item/adjustment_on_scene.cc \
    item/production_watcher_board.cc \
    item/material_fetch_watch_board.cc \
    item/storage_super_market.cc \
    item/information.cc \
    item/data_box.cc \
    item/board_info_flow.cc \
    item/improvement.cc \
    item/storage.cc \
    item/truck_transport.cc \
    item/other_company.cc \
    item/fifo.cc \
    item/product_to_customer.cc \
    item/MultiInputDialog.cc

HEADERS += \
    flow_app.h \
    defs.hpp \
    flow_main.h \
    drawer/toolbox.h \
    drawer/info_flow.h \
    canvas/body.h \
    canvas/scene.h \
    canvas/view.h \
    item/item.h \
    item/maker.hpp \
    item/material_flow.h \
    item/traditional_info_flow.h \
    item/electric_info_flow.h \
    drawer/drag_widget.h \
    item/board_station.h \
    drawer/drag_pixmap.h \
    item/cache_or_safe_storage.h \
    item/fetch_material.h \
    item/signal_board.h \
    item/sequence_pull_ball.h \
    item/balanced_production.h \
    item/operating_personnel.h \
    item/board_arrival.h \
    item/production_sequence.h \
    attribute_widget.h \
    item/adjustment_on_scene.h \
    item/improvement.h \
    item/production_watcher_board.h \
    item/material_fetch_watch_board.h \
    item/storage_super_market.h \
    item/information.h \
    item/data_box.h \
    item/board_info_flow.h \
    item/storage.h \
    item/truck_transport.h \
    item/other_company.h \
    item/fifo.h \
    item/product_to_customer.h \
    item/MultiInputDialog.h

FORMS += \
    flow_main.ui \
    remark_widget.ui

