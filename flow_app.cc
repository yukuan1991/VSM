#include "flow_app.h"
#include <QDir>
#include <QDebug>
#include "canvas_scene.h"

APP_REGISTER (flow_app)


flow_app::flow_app(int argc, char **argv)
    :application (argc, argv)
{

}

bool flow_app::run()
{
    main_ = std::make_unique<flow_main> ();

    QDir svg_dir ("svg");

    if (!svg_dir.exists ())
    {
        assert (false);
        flow_app::exit (-1);
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
