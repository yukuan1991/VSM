#include "flow_app.h"
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <algorithm>
#include "qt-tools/common.hpp"
#include "qt-tools/screen_saver.h"
#include "drawer/toolbox.h"

#include "item/circle.h"
#include "item/improve.h"
#include "item/reclaimer.h"
#include "item/board.h"
#include "item/convey.h"
#include "item/information.h"
#include "item/rectangles.h"
#include "item/round.h"
#include "item/square.h"
#include "item/square_text.h"
#include "item/supermarket_rectangles.h"
#include "item/three_rectangles.h"
#include "item/triangle.h"
#include "item/dispatch.h"
#include "item/buffer.h"
#include"item/communicate.h"




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


#include <QGraphicsView>
#include <QMatrix>
#include <QGraphicsScene>
#include <QGLWidget>

bool flow_app::run()
{
    //main_ = std::make_unique<flow_main> ();
    //main_->set_drawer ();
    //main_->show ();
    QGraphicsScene scene (0, 0, 800, 600);
    QGraphicsView view;
    view.setScene(&scene);
    QMatrix matrix;
    matrix.scale (2,2);
    view.setMatrix (matrix);
    view.setDragMode (decltype (view) :: RubberBandDrag);
    view.setRubberBandSelectionMode (Qt::IntersectsItemShape);
    view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    view.show();
    qDebug() << "main";

   auto p_item = item::communicate::make({150,150}, Qt::black);

    if (p_item != nullptr)

    {
        qDebug() << "main if";
        scene.addItem(p_item.release());
    }
    exec ();
    return false;
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
