#include "flow_app.h"
#include <QDir>
#include <QDebug>

APP_REGISTER (flow_app)


flow_app::flow_app(int argc, char **argv)
    :application (argc, argv)
{

}

bool flow_app::run()
{
    QDir svg_dir ("svg");

    if (!svg_dir.exists ())
    {
        assert (false);
        flow_app::exit (-1);
    }

    auto file_list = svg_dir.entryList (QStringList () << "*.svg");
    std::vector<std::string> str_file_list;
    str_file_list.reserve (static_cast<size_t> (file_list.size ()));

    for (auto & it : file_list)
    {
        str_file_list.emplace_back (it.toStdString ());
        qDebug () << it;
    }


    return false;
}
