#include "flow_app.h"
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <algorithm>
#include "canvas_scene.h"
#include "qt-tools/common.hpp"

APP_REGISTER (flow_app)

using namespace std;

flow_app::flow_app(int argc, char **argv)
    :application (argc, argv)
{
    go update_check;
}

bool flow_app::run()
{
    main_ = std::make_unique<flow_main> ();

    QDir svg_dir ("svg");

    if (!svg_dir.exists ())
    {
        QMessageBox::information (nullptr, "错误", "找不到svg文件夹");
        ::exit(-1);
    }

    auto file_list = svg_dir.entryInfoList (QStringList () << "*.svg");
    QStringList path_list;
    for (auto & it : file_list)
    {
        path_list.push_back (it.absoluteFilePath ());
    }

    main_->set_drawer (path_list);

    main_->show ();
    return true;
}

void flow_app::update_check()
{
    auto update_list = ::check_for_update (SERVER_ADDR, UPDATE_PATH, SOFTWARE_NAME);
    if (!update_list.empty())
    {

    }
}
