#include "drawer/toolbox.h"
#include <QDir>
#include "drawer/info_flow.h"
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "drawer/drag_widget.h"
#include "drawer/drag_pixmap.h"
#include <QPushButton>
#include <QDebug>

namespace drawer
<%

std::unique_ptr<toolbox> toolbox::make(QWidget* parent)
{
    auto ret = std::unique_ptr<toolbox> (new toolbox (parent, Qt::WindowFlags ()));

    if (ret == nullptr or !ret->init())
    {
        return nullptr;
    }
    else
    {
        return ret;
    }
}

QString toolbox::status()
{
    return status_;
}

toolbox::~toolbox()
{

}

toolbox::toolbox(QWidget *parent, Qt::WindowFlags f)
    :QToolBox (parent, f)
{
}

bool toolbox::init ()
{
    auto entity = init_entity();
    connect(entity.get(), &drag_widget::button_triggered, this, &toolbox::status_changed);
    connect(this, &toolbox::reset_status, entity.get (), &drag_widget::reset_status);
    addItem(entity.release(), "实体");

    auto material_flow = init_material_flow ();
    connect(material_flow.get(), &drag_widget::button_triggered, this, &toolbox::status_changed);
    connect(this, &toolbox::reset_status, material_flow.get (), &drag_widget::reset_status);
    addItem(material_flow.release(), "物流");

    auto info_flow = init_info_flow ();
    connect(info_flow.get(), &drag_widget::button_triggered, this, &toolbox::status_changed);
    connect(this, &toolbox::reset_status, info_flow.get (), &drag_widget::reset_status);
    addItem(info_flow.release(), "信息流");
    addItem (drag_widget::make({"改善"}).release (), {"改善"});

    connect (this, &toolbox::status_changed, [this] (const QString& s){ status_ = s; });

    return true;
}


///实体
std::unique_ptr<drag_widget> toolbox::init_entity()
{
    const vector<QString> items
    {
        "生产工序",
        "其他公司",
        "库存",
        "卡车运输",
        "库存超市",
        "信息",
        "生产看板",
        "取料看板",
        "信号看板",
        "顺序拉动球",
        "看板站",
        "看板以批量方式传达",
        "均衡生产",
        "现场调度",
        "缓冲或安全库存",
        "操作员",
        "生产控制部门",
        "增值比"

    };
    return drag_widget::make(items, {"文字"});

}
///物料流
std::unique_ptr<drag_widget> toolbox::init_material_flow()
{
    return drag_widget::make({"取料"}, {"物流", "先进先出", "成品发送至顾客"});
}

std::unique_ptr<drag_widget> toolbox::init_info_flow()
{
    return drag_widget::make({}, {"传统信息流", "电子信息流", "看板用信息流"});
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

void toolbox::on_button_pressed()
{
    auto button = dynamic_cast<QPushButton*> (sender());
    if (button == nullptr)
    {
        return;
    }

    auto name = button->text();
}

%>
