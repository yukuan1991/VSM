#include "canvas/body.h"
#include "json.hpp"
#include "utility/raii.hpp"
#include "defs.hpp"
#include <QDir>
#include "item/item.h"

namespace canvas
<%

body::body(QWidget *parent, QString svg_dir)
    :view (parent)
    ,svg_dir_ (::move (svg_dir))
{
    setScene (&scene_);
    init_conn ();
    is_untitled_ = true;
}

void body::file_new_title()
{

}

std::string body::dump()
{
    return item::item::dump_scene (scene ());
}

bool body::load(const std::string &data) try
{
    Q_UNUSED (data);
    return true;
}
catch (const std::exception& e)
{
    Q_UNUSED(e);
    return false;
}

QString body::get_path_from_name(const QString &name)
{
    QDir dir (svg_dir_);
    auto list = dir.entryInfoList();
    for (auto & file : list)
    {
        if (file.baseName() == name)
        {
            return file.filePath();
        }
    }

    throw std::logic_error ("cannot find svg_file ");
    return {};
}

void body::set_remark(const QString &remark)
{
    auto list = scene ()->selectedItems();
    if (list.size() != 1)
    {
        return;
    }

    list[0]->setData(remark_role, remark);
}

QString body::remark()
{
    auto list = scene ()->selectedItems();
    if (list.size() != 1)
    {
        return {};
    }

    auto remark = list[0]->data(remark_role).toString();
    return remark;
}

const nlohmann::json body::selected_item_data()
{
    return scene_.selected_item_attribute ();
}

void body::set_item_attribute(string_view key, std::string value)
{
    scene_.set_item_attribute (key, value);
}


void body::print_render(QPrinter *printer)
{
    QPainter painter(printer);
    scene ()->render(&painter, QRectF (), scene_.effective_rect ());
}

body::~body()
{

}


void body::window_modified()
{
    setWindowModified(true);
    setWindowTitle(cur_file_+"[*]");
}

void body::init_conn()
{
    connect (&scene_, &scene::selection_changed, this, &body::selection_changed);
}

%>
