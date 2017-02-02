#include "drawer/drag_pixmap.h"
#include <QMap>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QFontMetricsF>
#include <algorithm>


namespace drawer
<%
using namespace std;
using pixmap_maker = void (*)  (QPainter*, qreal, qreal);


static void board_station_maker (QPainter* painter, qreal width, qreal height);
static void fifo_maker (QPainter* painter, qreal width, qreal height);
static void fetch_material_maker (QPainter* painter, qreal width, qreal height);
static void production_sequence_maker (QPainter* painter, qreal width, qreal height);
static void other_company_maker (QPainter* painter, qreal width, qreal height);
static void data_box_maker (QPainter* painter, qreal width, qreal height);
static void storage_maker (QPainter* painter, qreal width, qreal height);
static void truck_transport_maker (QPainter* painter, qreal width, qreal height);
static void storage_super_market_maker (QPainter* painter, qreal width, qreal height);
static void information_maker (QPainter* painter, qreal width, qreal height);
static void production_watcher_board_maker (QPainter* painter, qreal width, qreal height);
static void material_fetch_watch_board_maker (QPainter* painter, qreal width, qreal height);
static void signal_board_maker (QPainter* painter, qreal width, qreal height);
static void sequence_pull_ball_maker (QPainter* painter, qreal width, qreal height);
static void board_station_maker (QPainter* painter, qreal width, qreal height);
static void board_arrival_maker (QPainter* painter, qreal width, qreal height);
static void balanced_production_maker (QPainter* painter, qreal width, qreal height);
static void adjustment_on_scene_maker (QPainter* painter, qreal width, qreal height);
static void improvement_maker (QPainter* painter, qreal width, qreal height);
static void cache_or_safe_storage_maker (QPainter* painter, qreal width, qreal height);
static void operator_maker (QPainter* painter, qreal width, qreal height);

QPixmap make_pixmap(const QString &name, qreal width, qreal height)
{
    QPixmap pm (static_cast<int> (width), static_cast<int> (height));
    pm.fill(Qt::transparent);

    static std::map<QString, pixmap_maker> item_map
    {
        {"看板站", board_station_maker},
        //{"生产工序", production_sequence_maker},
        //{"其他公司", other_company_maker},
        //{"数据箱", data_box_maker},
        //{"库存", storage_maker},
        //{"卡车运输", truck_transport_maker},
        //{"库存超市", storage_super_market_maker},
        //{"信息", information_maker},
        //{"生产看板", production_watcher_board_maker},
        //{"取料看板", material_fetch_watch_board_maker},
        {"信号看板", signal_board_maker},
        {"先进先出", fifo_maker},
        {"顺序拉动球", sequence_pull_ball_maker},
        {"看板以批量方式传达", board_arrival_maker},
        {"均衡生产", balanced_production_maker},
        //{"现场调度", adjustment_on_scene_maker},
        //{"改善", improvement_maker},
        {"取料", fetch_material_maker},
        {"缓冲或安全库存", cache_or_safe_storage_maker},
        {"操作员", operator_maker}
    };

    QPainter painter (&pm);

    auto found = item_map.find(name);

    if (found == item_map.end())
    {
        pm.fill(Qt::red);
    }
    else
    {
        (found->second) (&painter, width, height);
    }

    return pm;
}

void board_station_maker (QPainter* painter, qreal width, qreal height)
{
    const QPointF p1 {0.2 * width, 0.125 * height},
    p2 {0.8 * width, 0.125 * height},
    p3 {0.25 * width, 0.5 * height},
    p4 {0.5 * width, 0.5 * height},
    p5 {0.75 * width, 0.5 * height},
    p6 {0.25 * width, 0.875 * height},
    p7 {0.5 * width, 0.875 * height},
    p8 {0.75 * width, 0.875 * height};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(width / 50);
    painter->setPen(the_pen);

    ///给定坐标

    painter->drawLine(p1,p3);
    painter->drawLine(p3,p5);
    painter->drawLine(p5,p2);
    painter->drawLine(p4,p7);
    painter->drawLine(p6,p8);
}

static void production_sequence_maker (QPainter* painter, qreal width, qreal height)
{

}

static void other_company_maker (QPainter* painter, qreal width, qreal height)
{

}

static void data_box_maker (QPainter* painter, qreal width, qreal height)
{

}

static void storage_maker (QPainter* painter, qreal width, qreal height)
{

}

static void truck_transport_maker (QPainter* painter, qreal width, qreal height)
{

}

static void storage_super_market_maker (QPainter* painter, qreal width, qreal height)
{

}

static void information_maker (QPainter* painter, qreal width, qreal height)
{

}

static void production_watcher_board_maker (QPainter* painter, qreal width, qreal height)
{

}

static void material_fetch_watch_board_maker (QPainter* painter, qreal width, qreal height)
{

}

static void signal_board_maker (QPainter* painter, qreal width, qreal height)
{
    QPointF
    p1 {0.05 * width, height / 80},
    p2 {0.95 * width, height / 80},
    p3 {0.5 * width, 79 * height / 80};

    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1, p2, p3}}, Qt::WindingFill);
}

static void sequence_pull_ball_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);
    painter->drawEllipse(QRectF {0.2 * width, height / 8, 0.6 * width, height / 8 * 6});
    painter->drawEllipse(QRectF {0.35 * width, height / 80 * 25.0, 30.0, 30.0});
}

static void board_arrival_maker (QPainter* painter, qreal width, qreal height)
{
    QVector<QPointF> polygon_shape
    {
        {0.3 * width, 0.3 * height},
        {0.6375 * width, 0.3 * height},
        {0.7 * width, 0.3625 * height},
        {0.7 * width, 0.675 * height},
        {0.3 * width, 0.675 * height}
    };

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(width * 0.02);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);

    painter->drawPolygon({polygon_shape}, Qt::WindingFill);

    for (auto& it : polygon_shape)
    {
        it += QPointF (-0.1 * width, 0.1 * height);
    }

    painter->drawPolygon({polygon_shape}, Qt::WindingFill);

    for (auto& it : polygon_shape)
    {
        it += QPointF (-0.1 * width, 0.1 * height);
    }

    painter->drawPolygon({polygon_shape}, Qt::WindingFill);
}

static void balanced_production_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * width);
    painter->setPen(the_pen);

    QRectF rect (0.05 * width, 0.25 * height, 0.9 * width, 0.5 * height);


    QFontMetricsF metrics (painter->font());

    auto w = metrics.width("OXOX");
    auto h = metrics.height();
    auto center = rect.center();
    auto text_rect = QRectF (center.x() - 0.5 * w, center.y() - 0.5 * h, w, h);

    painter->drawRect(rect);
    painter->drawText(text_rect,"OXOX", Qt::AlignVCenter | Qt::AlignCenter);
}

static void adjustment_on_scene_maker (QPainter* painter, qreal width, qreal height)
{

}

static void improvement_maker (QPainter* painter, qreal width, qreal height)
{

}

static void cache_or_safe_storage_maker (QPainter* painter, qreal width, qreal height)
{
    QPointF
    p1{0.35 * width ,0.125 * height},
    p2{0.65 * width,0.125 * height},
    p3{0.35 * width,0.875 * height},
    p4{0.65 * width,0.875 * height},
    p5{0.35 * width,0.375 * height},
    p6{0.65 * width,0.375 * height},
    p7{0.35 * width,0.625 * height},
    p8{0.65 * width,0.625 * height};
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    painter->setPen(the_pen);
    //给定坐标
    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1,p2,p4,p3}},Qt::WindingFill);
    painter->drawLine(p5,p6);
    painter->drawLine(p7,p8);
}

static void operator_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * width);
    painter->setPen(the_pen);

    painter->drawArc(QRectF{0.1 * width, height * 10 / 80, 0.8 * width, height * 60 / 80}, 180 * 16, 180 * 16);
    painter->drawArc(QRectF{0.3 * width, height * 20 / 80, 0.4 * width, height * 40 / 80}, 0 * 16, 360 * 16);
}

static void fetch_material_maker (QPainter* painter, qreal width, qreal height)
{
    QPointF
    p1 {0.75 * width, 0.8125 * height},
    p2 {0.82 * width, 0.9 * height},
    p3 {0.87 * width,0.75 * height};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(width / 50);
    painter->setPen(the_pen);

    //给定坐标
    painter->setBrush(Qt::white);

    painter->drawArc(QRectF{0.125 * width, height * 2.5 / 80, 0.75 * width, height * 75 / 80}, 45 * 16, 270 * 16);
    painter->setBrush(Qt::black);
    painter->drawPolygon({{p1,p2,p3}},Qt::WindingFill);
}

static void fifo_maker (QPainter* painter, qreal width, qreal height)
{

}

%>
