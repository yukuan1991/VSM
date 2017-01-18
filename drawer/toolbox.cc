#include "drawer/toolbox.h"
#include "drawer/list.h"
#include <QDir>
#include "drawer/info_flow.h"

namespace drawer
<%

std::unique_ptr<toolbox> toolbox::make(const QString &entity_dir,
                                       const QString& material_flow_dir,
                                       QWidget *parent)
{
    auto ret = std::unique_ptr<toolbox> (new toolbox (parent, Qt::WindowFlags ()));

    if (ret == nullptr or !ret->init(entity_dir, material_flow_dir))
    {
        return nullptr;
    }
    else
    {
        return ret;
    }
}

toolbox::~toolbox()
{

}

toolbox::toolbox(QWidget *parent, Qt::WindowFlags f)
    :QToolBox (parent, f)
{

}

bool toolbox::init (const QString &entity_dir, const QString& material_flow_dir)
{
    entity_ = std::make_unique<list> (this);
    material_flow_ = std::make_unique<list> (this);
    info_flow_ = info_flow::make(this, {"传统信息流", "电子信息流", "看板用信息流"});

    addItem(entity_.get(), "实体");
    addItem(info_flow_.get(), "信息流");
    addItem(material_flow_.get(), "物流");

    connect (info_flow_.get (), &info_flow::status_changed, [this] (auto&&s) { this->status_changed (s); });

    entity_->set_data(get_file_names(entity_dir));

    material_flow_->set_data(get_file_names(material_flow_dir));
    return true;
}

QStringList toolbox::get_file_names(const QDir &dir)
{
    QDir svg_dir (dir);
    auto file_list = svg_dir.entryInfoList (QStringList () << "*.svg");
    QStringList path_list;

    for (auto & it : file_list)
    {
        path_list.push_back (it.absoluteFilePath ());
    }
    return path_list;
}

%>
