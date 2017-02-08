#include "canvas/body.h"
#include "json.hpp"
#include "utility/raii.hpp"
#include "defs.hpp"
#include <QDir>
#include "flow_utility.h"

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
    nlohmann::json data;
    nlohmann::json items = nlohmann::json::array();
    for (auto & it : this->items())
    {
        nlohmann::json item_data;
        item_data ["scale"] = it->matrix().m11();
        item_data ["pos"]["x"] = it->pos().x ();
        item_data ["pos"]["y"] = it->pos().y ();
        item_data ["z-value"] = it->zValue();
        item_data ["type"] = it->data(path_role).toString ().toStdString ();
        item_data ["remark"] = it->data(remark_role).toString().toStdString();
        items.push_back(::move (item_data));
    }
    data ["items"] = ::move (items);
    data ["view-scale"] = matrix().m11 ();
    auto view_geo = viewport()->geometry();
    auto visible_area = mapToScene (view_geo).boundingRect();
    data ["area"]["x"] = visible_area.x();
    data ["area"]["y"] = visible_area.y();
    data ["area"]["w"] = visible_area.width();
    data ["area"]["h"] = visible_area.height();

    return data.dump(4);
}

bool body::load(const std::string &data) try
{
    this->scene()->clear();

    SCOPE_FAIL { scene ()->clear(); };

    auto json_data = nlohmann::json::parse(data);
    double scale_factor = json_data ["view-scale"];

    QMatrix matrix;
    matrix.scale(scale_factor, scale_factor);

    setMatrix(matrix);

    for (auto & it : json_data ["items"])
    {
        std::string type = it ["type"];
        double x = it ["pos"]["x"];
        double y = it ["pos"]["y"];
        auto path = get_path_from_name(type.data());
        auto item = add_svg_to_scene (path, scene (), QPointF (x, y));

        double z_value = it ["z-value"];
        item->setZValue(z_value);

        double scale = it ["scale"];
        item->setMatrix(QMatrix ().scale(scale, scale));

        std::string remark = it ["remark"];
        item->setData(remark_role, remark.data());
    }

    return true;
}
catch (const std::exception& e)
{
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

void body::window_modified()
{
    setWindowModified(true);
    setWindowTitle(cur_file_+"[*]");
}

void body::init_conn()
{
    connect(&scene_, &scene::selection_changed, [this] (bool ok){ emit selection_changed (ok); });
}

%>
