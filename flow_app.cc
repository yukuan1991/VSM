#include "flow_app.h"
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <algorithm>
#include "qt-tools/common.hpp"
#include "qt-tools/screen_saver.h"
#include "drawer/toolbox.h"
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

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMatrix>
#include <QGLWidget>
#include "item/material_flow.h"



#include "item/adjustment_on_scene.h"
#include "item/improvement.h"

#include "item/production_watcher_board.h"
#include "item/material_fetch_watch_board.h"
#include "item/storage_super_market.h"
#include "item/cache_or_safe_storage.h"
#include "item/material_fetch_watch_board.h"
#include "item/production_sequence.h"
#include "item/production_watcher_board.h"
#include "item/data_box.h"
#include "item/information.h"
#include "item/balanced_production.h"
bool flow_app::run()
{
    main_ = std::make_unique<flow_main> ();
    main_->set_drawer ();
    main_->show ();
//    QGraphicsScene scene (0, 0, 800, 600);
//    QGraphicsView view;
//    view.setScene(&scene);
//    QMatrix matrix;
//    matrix.scale (2,2);
//    view.setMatrix (matrix);
//    view.setDragMode (decltype (view) :: RubberBandDrag);
//    view.setRubberBandSelectionMode (Qt::IntersectsItemShape);
//    view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
//    view.show();
//    qDebug() << "main";

//    auto p_item = item::adjustment_on_scene::make({150, 150},Qt::black);

//    if (p_item != nullptr)

//    {
//        qDebug() << "main if";

//        scene.addItem(p_item.release());
//    }    return exec();
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
