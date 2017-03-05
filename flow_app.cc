#include "flow_app.h"
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <algorithm>
#include "qt-tools/common.hpp"
#include "qt-tools/screen_saver.h"
#include "drawer/toolbox.h"
#include <QGraphicsScene>
#include <QMatrix>
#include <QGLWidget>
#include <QGLWidget>

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
    main_->set_drawer ();
    main_->show ();
    return true ;
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
