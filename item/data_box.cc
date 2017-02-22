#include "data_box.h"
#include <QPainter>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QInputDialog>

///数据箱
   ///修改完成
namespace item {


data_box::data_box(json data, QPointF pos, item* parent)
    :fixed_item (::move(data), pos, parent)
{

   // connect(button_ok, SIGNAL(clicked()), this, SLOT(get_edit_text()));

}

void data_box::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     Q_UNUSED(widget);

    QPointF
    p1_ {0.01* item_width_, 0.0125 * item_height_},
    p2_ {0.99 * item_width_, 0.0125 * item_height_},
    p3_ {0.01 * item_width_, 0.25 * item_height_},
    p4_ {0.99 * item_width_, 0.25 * item_height_},
    p5_ {0.01 * item_width_, 0.5 * item_height_},
    p6_ {0.99 * item_width_, 0.5 * item_height_},
    p7_ {0.01 * item_width_, 0.7375 * item_height_},
    p8_ {0.99 * item_width_, 0.7375 * item_height_},
    p9_ {0.01 * item_width_, 0.9875 * item_height_},
    p10_ {0.99 * item_width_, 0.9875 * item_height_};

    auto the_pen = painter->pen ();
    the_pen.setColor(color ());
    the_pen.setWidthF(item_width_ * 0.02);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1_, p2_, p10_, p9_}},Qt::WindingFill);
    painter->drawLine(p5_,p6_);
    painter->drawLine(p7_,p8_);
    painter->drawLine(p3_,p4_);

    QFontMetricsF metrics (painter->font());
    auto height = metrics.height();

    auto center_1 = QPointF (item_width_ / 2, (p1_.y() + p3_.y() ) / 2);
    auto center_2 = QPointF (item_width_ / 2, (p5_.y() + p7_.y() ) / 2);
    auto center_3 = QPointF (item_width_ / 2, (p3_.y() + p5_.y() ) / 2);
    auto center_4 = QPointF (item_width_ / 2, (p7_.y() + p9_.y() ) / 2);

    auto value_a = find_json_value("a", item_info_["etc"]);
    auto value_b = find_json_value("b", item_info_["etc"]);
    auto value_c = find_json_value("c", item_info_["etc"]);
    auto value_d = find_json_value("d", item_info_["etc"]);

    qreal width = 0;
    width = metrics.width (value_a.data());
    painter->drawText(QRectF (center_1 - QPointF (width / 2, height / 2), QSizeF (width, height)), value_a.data ());
    width = metrics.width (value_b.data ());
    painter->drawText(QRectF (center_2 - QPointF (width / 2, height / 2), QSizeF (width, height)), value_b.data ());
    width = metrics.width (value_c.data ());
    painter->drawText(QRectF (center_3 - QPointF (width / 2, height / 2), QSizeF (width, height)), value_c.data ());
    width = metrics.width (value_d.data ());
    painter->drawText(QRectF (center_4 - QPointF (width / 2, height / 2), QSizeF (width, height)), value_d.data ());

    item::paint(painter, option, widget);
}

void data_box::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

    std::string str_a = find_json_value("a", item_info_["etc"]);
    std::string str_b = find_json_value("b", item_info_["etc"]);
    std::string str_c = find_json_value("c", item_info_["etc"]);
    std::string str_d = find_json_value("d", item_info_["etc"]);

    auto data = set_box_data (::move (str_a), ::move (str_b), ::move (str_c), ::move (str_d));

    if (data)
    {
        auto& data_value = data.value ();
        item_info_["etc"]["a"] = get<0> (data_value);
        item_info_["etc"]["b"] = get<1> (data_value);
        item_info_["etc"]["c"] = get<2> (data_value);
        item_info_["etc"]["d"] = get<3> (data_value);
    }
}


optional<tuple<string, string, string, string>> data_box::set_box_data(string a, string b, string c, string d)
{
    QDialog dlg;
    auto layout = new QGridLayout (&dlg);
    auto label_a = new QLabel ("a", &dlg);
    auto label_b = new QLabel ("b", &dlg);
    auto label_c = new QLabel ("c", &dlg);
    auto label_d = new QLabel ("d", &dlg);

    auto edit_a = new QLineEdit (a.data (), &dlg);
    auto edit_b = new QLineEdit (b.data (), &dlg);
    auto edit_c = new QLineEdit (c.data (), &dlg);
    auto edit_d = new QLineEdit (d.data (), &dlg);

    auto button_confirm = new QPushButton ("完成", &dlg);

    layout->addWidget (label_a, 0, 0);
    layout->addWidget (edit_a, 0, 1);
    layout->addWidget (label_b, 1, 0);
    layout->addWidget (edit_b, 1, 1);
    layout->addWidget (label_c, 2, 0);
    layout->addWidget (edit_c, 2, 1);
    layout->addWidget (label_d, 3, 0);
    layout->addWidget (edit_d, 3, 1);
    layout->addWidget (button_confirm, 4, 1);

    connect (button_confirm, &QPushButton::clicked, &dlg, &QDialog::accept);

    auto pos = QCursor::pos();
    pos -= QPoint (dlg.width() / 2, dlg.height() / 2);
    dlg.move(pos);
    if (dlg.exec () == QDialog::Accepted)
    {
        return make_tuple (edit_a->text().toStdString(), edit_b->text().toStdString(),
                           edit_c->text().toStdString(), edit_d->text().toStdString()
                           );
    }

    return {};
}

std::unique_ptr<data_box> data_box::make(json data, QPointF pos, item* parent)
{
    std::unique_ptr<data_box> ret(new data_box(::move(data), pos, parent));
    if(!ret->init ())
    {
        return nullptr;
    }
    else
    {
       return ret;
    }
}

bool data_box::init()
{
    set_item_type("数据箱");
    set_z_value(303);

    return true;
}

}
