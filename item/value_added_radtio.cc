#include "value_added_radtio.h"
#include <QPainter>
#include <QDebug>
#include <boost/algorithm/string.hpp>
namespace item {


value_added_radtio::value_added_radtio(item* parent)
    :item(parent)
{
    set_attribute("生产交付周期");
    set_attribute("增值时间");

}

void value_added_radtio::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto x_scale = (item_width_ / 100);
    auto y_scale = item_height_ / 80;

    QPointF p1{1 * x_scale, 1 * y_scale},
    p2{149 * x_scale, 1 * y_scale},
    p3{1 * x_scale, 40 * y_scale},
    p4{149 * x_scale, 40 * y_scale},
    p5{1 * x_scale, 79 * y_scale},
    p6{149 * x_scale, 79 * y_scale};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(std::max(item_width_ * 0.02,2.0));
    painter->setBrush(Qt::white);
    painter->setPen(the_pen);
    painter->drawPolygon({{p1,p2,p6,p5}},Qt::WindingFill);
    painter->drawLine(p3,p4);

    item::paint(painter,option,widget);

}

void value_added_radtio::paint_attribute(QPainter *painter)
{
    auto production_period = attribute ("生产交付周期");
    auto added_timespan = attribute ("增值时间");
    qDebug () << production_period.data ();
    qDebug () << added_timespan.data ();

    boost::trim (production_period);
    boost::trim (added_timespan);

    auto x_scale = (item_width_ / 100);
    auto y_scale = item_height_ / 80;
    QPointF p1{1 * x_scale, 1 * y_scale},
    p2{149 * x_scale, 1 * y_scale},
    p3{1 * x_scale, 40 * y_scale},
    p4{149 * x_scale, 40 * y_scale},
    p5{1 * x_scale, 79 * y_scale},
    p6{149 * x_scale, 79 * y_scale};

    QRectF top_rect (p1, p4);
    QRectF bottom_rect (p3, p6);

    QFontMetricsF metrics (painter->font ());

    auto top_text = "生产交付周期=" + production_period;
    auto bottom_text = "增值时间=" + added_timespan;

    auto w_top = metrics.width(top_text.data ());
    auto w_bottom = metrics.width(bottom_text.data ());
    auto h = metrics.height ();

    if (!production_period.empty ())
    {
        painter->drawText (QRectF (top_rect.center() - QPointF (w_top / 2, h / 2), QSizeF (w_top, h)),
                           top_text.data ());
    }
    if (!added_timespan.empty ())
    {
        painter->drawText (QRectF (bottom_rect.center() - QPointF (w_bottom / 2, h / 2),
                                   QSizeF (w_bottom, h)), bottom_text.data ());
    }
}

QRectF value_added_radtio::boundingRect() const
{
    auto x_scale = (item_width_ / 100);
    auto y_scale = item_height_ / 80;
    return {0, 0, 150 * x_scale, 80 * y_scale};
}

std::unique_ptr<value_added_radtio> value_added_radtio::make(QPointF pos, QColor color)
{
    std::unique_ptr<value_added_radtio> ret(new value_added_radtio);
    ret->setPos(pos);
    ret->set_color(std::move(color));
    ret->type_ = "增值比";
    return ret;
}
}
