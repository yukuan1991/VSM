#include "drawer/drag_pixmap.h"
#include <QMap>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QFontMetricsF>
#include <algorithm>
#include <QLineF>


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
static void finished_product_to_customer_maker (QPainter* painter, qreal width, qreal height);
static void operating_personnel (QPainter* painter, qreal width, qreal height);

QPixmap make_pixmap(const QString &name, qreal width, qreal height)
{
    QPixmap pm (static_cast<int> (width), static_cast<int> (height));
    pm.fill(Qt::transparent);

    static std::map<QString, pixmap_maker> item_map
    {
        {"看板站", board_station_maker},
        {"生产工序", production_sequence_maker},
        {"成品发送至顾客", finished_product_to_customer_maker},
        {"数据箱", data_box_maker},
        //{"其他公司", other_company_maker},
        {"数据箱", data_box_maker},
        {"库存", storage_maker},
        {"卡车运输", truck_transport_maker},
        {"库存超市", storage_super_market_maker},
        {"信息", information_maker},
        {"生产看板", production_watcher_board_maker},
        {"取料看板", material_fetch_watch_board_maker},
        {"信号看板", signal_board_maker},
        {"先进先出", fifo_maker},
        {"顺序拉动球", sequence_pull_ball_maker},
        {"看板以批量方式传达", board_arrival_maker},
        {"均衡生产", balanced_production_maker},
        //{"现场调度", adjustment_on_scene_maker},
        {"改善", improvement_maker},
        {"取料", fetch_material_maker},
        {"缓冲或安全库存", cache_or_safe_storage_maker},
        {"操作员", operating_personnel}
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
    auto the_pen = painter->pen ();
    the_pen.setColor (Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;
    painter->drawLine (QPointF {x_scale * 1, y_scale * 1}, {x_scale * 99, y_scale * 1});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 28}, {x_scale * 99, y_scale * 28});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 79}, {x_scale * 99, y_scale * 79});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 1}, {x_scale * 1, y_scale * 79});
    painter->drawLine (QPointF {x_scale * 99, y_scale * 1}, {x_scale * 99, y_scale * 79});
}

static void other_company_maker (QPainter* painter, qreal width, qreal height)
{

}

static void data_box_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;
    painter->drawLine (QPointF {x_scale * 1,y_scale * 1}, {x_scale * 99,y_scale * 1});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 20}, {x_scale * 99, y_scale * 20});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 40}, {x_scale * 99, y_scale * 40});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 59}, {x_scale * 99, y_scale * 59});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 79}, {x_scale * 99, y_scale * 79});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 1}, {x_scale * 1,y_scale * 79});
    painter->drawLine (QPointF {x_scale * 99,y_scale * 1}, {x_scale * 99, y_scale * 79});
}

static void storage_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;
    painter->drawLine (QPointF {x_scale * 49, y_scale * 1}, {x_scale * 99, y_scale * 79});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 79}, {x_scale * 99, y_scale * 79});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 79}, {x_scale * 49, y_scale * 1});
    QFont font;
    font.setPointSize(20);
    QFontMetricsF metrics (font);
    auto text_height = metrics.height();
    auto text_width = metrics.width("I");
    QRectF text_rect {x_scale * 49-text_width/2,y_scale * 40,text_width,text_height};
    painter->setFont(font);
    painter->drawText(text_rect, "I", Qt::AlignVCenter | Qt::AlignCenter);
}

static void truck_transport_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;
    painter->drawLine (QPointF {x_scale * 1,y_scale * 1}, {x_scale * 69, y_scale * 1});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 55}, {x_scale * 1,y_scale * 1});
    painter->drawLine (QPointF {x_scale * 69, y_scale * 1}, {x_scale * 69, y_scale * 55});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 55}, {x_scale * 69, y_scale * 55});
    painter->drawLine (QPointF {x_scale * 69, y_scale * 25},{x_scale * 99, y_scale * 25});
    painter->drawLine (QPointF {x_scale * 99, y_scale * 25}, {x_scale * 99,y_scale * 55});
    painter->drawLine (QPointF {x_scale * 99, y_scale * 55}, {x_scale * 69, y_scale * 55});
    painter->setBrush(Qt::black);
    painter->drawEllipse (QPointF {x_scale * 17, y_scale * 65}, x_scale * 12, x_scale * 12);
    painter->drawEllipse (QPointF {x_scale * 72, y_scale * 65}, x_scale * 12, x_scale * 12);
}

static void storage_super_market_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;
    painter->drawLine (QPointF {x_scale * 1,y_scale * 1}, {x_scale * 99, y_scale * 1});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 27}, {x_scale * 99, y_scale * 27});
    painter->drawLine (QPointF {x_scale * 99, y_scale * 1}, {x_scale * 99, y_scale * 79});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 53}, {x_scale * 99, y_scale * 53});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 79}, {x_scale * 99, y_scale * 79});
}

static void information_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setWidthF(2.0);
    the_pen.setColor(Qt::black);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;
    painter->drawLine(QPointF {x_scale * 1,y_scale * 1}, {x_scale * 99, y_scale * 1});
    painter->drawLine (QPointF {x_scale * 99,y_scale * 1}, {x_scale * 99,y_scale * 79});
    painter->drawLine (QPointF {x_scale * 99, y_scale * 79}, {x_scale * 1, y_scale * 79});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 79}, {x_scale * 1,y_scale * 1});
}

static void production_watcher_board_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setWidthF(2.0);
    the_pen.setColor(Qt::black);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;
    painter->drawLine (QPointF {x_scale * 1,y_scale * 1}, {x_scale * 85, y_scale * 1});
    painter->drawLine (QPointF {x_scale * 85, y_scale * 1}, {x_scale * 99, y_scale * 16});
    painter->drawLine (QPointF {x_scale * 99, y_scale * 16}, {x_scale * 99, y_scale * 79});
    painter->drawLine (QPointF {x_scale * 99, y_scale * 79}, {x_scale * 1, y_scale * 79});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 79}, {x_scale * 1, y_scale * 1});
}

static void material_fetch_watch_board_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setWidthF(2.0);
    the_pen.setColor(Qt::black);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;
    painter->drawLine (QPointF {x_scale * 1, y_scale * 39}, {x_scale * 25, y_scale * 1});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 1}, {x_scale * 85,y_scale * 1});
    painter->drawLine (QPointF {x_scale * 85, y_scale * 1}, {x_scale * 99, y_scale * 16});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 1}, {x_scale * 1,y_scale * 79});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 79}, {x_scale * 99,y_scale * 79});
    painter->drawLine (QPointF {x_scale * 99, y_scale * 79}, {x_scale * 99, y_scale * 16});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 79}, {x_scale * 50, y_scale * 1});
    painter->drawLine (QPointF {x_scale * 25, y_scale * 79}, {x_scale * 74, y_scale * 1});
    painter->drawLine (QPointF {x_scale * 50, y_scale * 79}, {x_scale * (99+85)/2,y_scale * (16+1)/2});
    painter->drawLine (QPointF {x_scale * 74, y_scale * 79}, {x_scale * 99, y_scale * 39});
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
    painter->drawLine (QPointF (0, 0), QPointF (100, 80));

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
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::red);
    the_pen.setWidthF(0.02 * width);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;
    painter->drawLine(QPointF {x_scale * 1,y_scale * 8}, {x_scale * 33,y_scale * 23});
    painter->drawLine (QPointF {x_scale * 33, y_scale * 23}, {x_scale * 38, y_scale * 10});
    painter->drawLine (QPointF {x_scale * 38,y_scale * 10}, {x_scale * 49, y_scale * 21});
    painter->drawLine (QPointF {x_scale * 49, y_scale * 21}, {x_scale * 65, y_scale * 1});
    painter->drawLine (QPointF {x_scale * 65, y_scale * 1}, {x_scale * 64, y_scale * 19});
    painter->drawLine (QPointF {x_scale * 64, y_scale * 19}, {x_scale * 82, y_scale * 17});
    painter->drawLine (QPointF {x_scale * 82, y_scale * 17}, {x_scale * 76, y_scale * 26});
    painter->drawLine (QPointF {x_scale * 76, y_scale * 26}, {x_scale * 93, y_scale * 30});
    painter->drawLine (QPointF {x_scale * 93, y_scale * 30}, {x_scale * 80, y_scale * 37});
    painter->drawLine (QPointF {x_scale * 80, y_scale * 37}, {x_scale * 97, y_scale * 48});
    painter->drawLine (QPointF {x_scale * 97, y_scale * 48}, {x_scale * 77, y_scale * 47});
    painter->drawLine (QPointF {x_scale * 77, y_scale * 47}, {x_scale * 80, y_scale * 62});
    painter->drawLine (QPointF {x_scale * 80, y_scale * 62}, {x_scale * 64, y_scale * 53});
    painter->drawLine (QPointF {x_scale * 64, y_scale * 53}, {x_scale * 59, y_scale * 68});
    painter->drawLine (QPointF {x_scale * 59, y_scale * 68}, {x_scale * 48, y_scale * 55});
    painter->drawLine (QPointF {x_scale * 48, y_scale * 55}, {x_scale * 39, y_scale * 74});
    painter->drawLine (QPointF {x_scale * 39, y_scale * 74}, {x_scale * 35, y_scale * 57});
    painter->drawLine (QPointF {x_scale * 35, y_scale * 57}, {x_scale * 22, y_scale * 62});
    painter->drawLine (QPointF {x_scale * 22, y_scale * 62}, {x_scale * 25, y_scale * 51});
    painter->drawLine (QPointF {x_scale * 25, y_scale * 51}, {x_scale * 1, y_scale * 52});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 52}, {x_scale * 17, y_scale * 42});
    painter->drawLine (QPointF {x_scale * 17, y_scale * 42}, {x_scale * 1, y_scale * 31});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 31}, {x_scale * 20, y_scale * 27});
    painter->drawLine (QPointF {x_scale * 20, y_scale * 27}, {x_scale * 1, y_scale * 8});
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

static void operating_personnel (QPainter* painter, qreal width, qreal height)
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

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(width * 0.02);
    painter->setPen(the_pen);

    const QLineF
            top_line (0.05 * width, height / 3, 0.95 * width, height / 3),
            bottom_line (0.05 * width, height / 3 * 2, 0.95 * width, height / 3 * 2);

    /// Set Bold
    auto font = painter->font();
    font.setBold(true);
    painter->setFont(font);

    /// Mesure font size
    QFontMetricsF metrics (painter->font());
    auto font_width = metrics.width("FIFO");
    auto font_height = metrics.height();
    auto mid_point = QPointF (width / 2, height / 2);

    auto text_rect = QRectF (mid_point - QPointF {font_width / 2, font_height / 2},
                             QSizeF {font_width, font_height});

    painter->drawLine(top_line);
    painter->drawLine(bottom_line);
    painter->drawLine(QPointF (0.05 * width, height / 2),
                      QPointF (text_rect.left() - 0.05 * width, height / 2));

    painter->drawText(text_rect, "FIFO", Qt::AlignHCenter | Qt::AlignVCenter);
    painter->drawLine(QPointF (text_rect.right() + 0.05 * width, height / 2),
                      QPointF (0.9 * width, height / 2));

    QPointF top_tip (0.9 * width, height / 2 + height * 2 / 80);
    QPointF bottom_tip (0.9 * width, height / 2 - height * 2 / 80);
    QPointF mid_tip (0.95 * width, height / 2);

    the_pen.setWidthF(0.01 * width);
    painter->setPen(the_pen);

    painter->setBrush(Qt::black);
    painter->drawPolygon({{top_tip, bottom_tip, mid_tip}}, Qt::WindingFill);
}


static void finished_product_to_customer_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;
    painter->drawLine (QPointF {x_scale * 1,y_scale * 20}, {x_scale * 79, y_scale * 20});
    painter->drawLine (QPointF {x_scale * 79, y_scale * 20}, {x_scale * 79,y_scale * 1});
    painter->drawLine (QPointF {x_scale * 79,y_scale * 1}, {x_scale * 99,y_scale * 38});
    painter->drawLine (QPointF {x_scale * 99,y_scale * 38}, {x_scale * 79,y_scale * 77});
    painter->drawLine (QPointF {x_scale * 79,y_scale * 77}, {x_scale * 79,y_scale * 56});
    painter->drawLine (QPointF {x_scale * 79, y_scale * 56}, {x_scale * 1,y_scale * 56});
    painter->drawLine (QPointF {x_scale * 1,y_scale * 56}, {x_scale * 1,y_scale * 20});
}

%>
