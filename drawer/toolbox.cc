#include "drawer/toolbox.h"
#include "drawer/list.h"
#include <QDir>
#include "drawer/info_flow.h"
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "drawer/drag_widget.h"
#include "drawer/drag_pixmap.h"
#include <QPushButton>

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
    return {};
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
    addItem(init_entity().release(), "实体");
    //addItem(info_flow_.get(), "信息流");
    addItem(init_material_flow().release(), "物流");

    //connect (info_flow_.get (), &info_flow::status_changed, [this] (auto&&s) { this->status_changed (s); });

    return true;
}

std::unique_ptr<drag_widget> toolbox::init_entity()
{
    auto ret = std::make_unique<drag_widget> ();
    const QString items []
    {
        "生产工序",
        "取料",
        "其他公司",
        "数据箱",
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
        "改善",
        "缓冲或安全库存",
        "操作员",
    };

    auto v_layout = new QVBoxLayout(ret.get());
    for (auto & it : items)
    {
        auto map = drawer::make_pixmap (it, 100, 80);

        auto pic_label = new QLabel (ret.get());
        pic_label->setObjectName(it);
        pic_label->setPixmap(map.scaled(100, 80));
        v_layout->addWidget (pic_label);

        auto info_label = new QLabel (it, ret.get());
        info_label->setObjectName({});
        v_layout->addWidget (info_label);
    }

    v_layout->addItem (new QSpacerItem (0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    return ret;
}

std::unique_ptr<drag_widget> toolbox::init_material_flow()
{
    auto ret = std::make_unique<drag_widget> ();
    const QString items []
    {
        "取料",
        "先进先出",
        "成品发送至顾客"
    };

    auto v_layout = new QVBoxLayout(ret.get());
    for (auto & it : items)
    {
        auto map = drawer::make_pixmap (it, 100, 80);

        auto pic_label = std::make_unique<QLabel> (ret.get ());
        pic_label->setObjectName(it);
        pic_label->setPixmap(map.scaled(100, 80));
        v_layout->addWidget (pic_label.release ());

        auto info_label = std::make_unique<QLabel> (it, ret.get ());
        info_label->setObjectName({});
        info_label->setAlignment(Qt::AlignHCenter);
        v_layout->addWidget (info_label.release());
    }

    auto button_push = std::make_unique<QPushButton> (drawer::make_pixmap("推动", 100, 80), "", ret.get ());
    button_push->setIconSize({100, 80});
    v_layout->addWidget(button_push.release());

    auto info_label = std::make_unique<QLabel> ("推动", ret.get ());
    info_label->setObjectName({});
    info_label->setAlignment(Qt::AlignHCenter);
    v_layout->addWidget (info_label.release());

    v_layout->addItem (new QSpacerItem (0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    return ret;
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
