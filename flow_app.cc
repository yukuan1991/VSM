#include "flow_app.h"
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <algorithm>
#include "canvas_scene.h"
#include "qt-tools/common.hpp"
#include "qt-tools/screen_saver.h"

APP_REGISTER (flow_app)

using namespace std;
using json = nlohmann::json;

flow_app::flow_app(int argc, char **argv)
    :application (argc, argv)
{
    if (argc < 2)
    {
        go  [this] { update_check (); };
    }
}

bool flow_app::run()
{
    main_ = std::make_unique<flow_main> ();

    QDir svg_dir (SVG_DIR);

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

void flow_app::exec_update(std::vector<std::pair<string, string>> file_info)
{
    if (!::ask (nullptr, "更新", "有新的版本，是否更新"))
    {
        return;
    }

    auto json_file_info = json::array ();
    for (auto & it : file_info)
    {
        json_file_info.push_back ({{"path", it.first}, {"md5", it.second}});
    }

    nlohmann::json json_param {
        {"prefix", UPDATE_FILE_PATH},
        {"files", ::move (json_file_info)},
        {"exec", EXEC_FILE},
        {"server_addr", SERVER_ADDR}
    };

    auto parameter = ::binary_to_base64 (json_param.dump ());

    ::system (("start "s + UPDATE_PATH + " " + parameter).data ());
    flow_app::exit (0);
}

void flow_app::update_check()
{
    auto files = ::check_for_update (SERVER_ADDR, "/schedule/update", SOFTWARE_NAME);
    if (files.empty ())
    {
        return;
    }

    call_after [this, files = ::move (files)] () mutable
    {
        this->exec_update (::move (files));
    };
}
