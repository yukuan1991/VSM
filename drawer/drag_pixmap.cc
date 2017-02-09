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
static void tradition_info_flow_maker(QPainter* painter, qreal width, qreal height);
static void electric_info_flow_maker(QPainter* painter,qreal width,qreal height);
static void board_info_flow_maker(QPainter* painter, qreal width,qreal height);
static void material_flow_maker(QPainter* painter,qreal width, qreal height);

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
        {"其他公司", other_company_maker},
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
        {"现场调度", adjustment_on_scene_maker},
        {"改善", improvement_maker},
        {"取料", fetch_material_maker},
        {"缓冲或安全库存", cache_or_safe_storage_maker},
        {"操作员", operating_personnel},
        {"传统信息流", tradition_info_flow_maker},
        {"电子信息流", electric_info_flow_maker},
        {"看板用信息流", board_info_flow_maker},
        {"物流", material_flow_maker}
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

    QVector<QPointF> polygon_shape
    {
        {x_scale * 1, y_scale * 1},
        {x_scale * 99, y_scale * 1},
        {x_scale * 99, y_scale * 79},
        {x_scale * 1, y_scale * 79}
    };
    painter->setBrush(Qt::white);
    painter->drawPolygon({polygon_shape}, Qt::WindingFill);

    painter->drawLine (QPointF {x_scale * 1, y_scale * 28}, {x_scale * 99, y_scale * 28});
}

static void other_company_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);

    auto x_scale = width / 100;
    auto y_scale = height / 80;
    const QPointF
    p1 {1 * x_scale, 30 * y_scale},
    p2 {33 * x_scale,1 * y_scale},
    p3 {33 * x_scale,26 * y_scale},
    p4 {66 * x_scale,1 * y_scale},
    p5 {66 * x_scale,26 * y_scale},
    p6 {99 * x_scale,4 * y_scale},
    p7 {99 * x_scale,79 * y_scale},
    p8 {1 * x_scale,79 * y_scale};
    painter->drawPolygon({{p1,p2,p3,p4,p5,p6,p7,p8}},Qt::WindingFill);
}

static void data_box_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;

    QVector<QPointF> polygon_shape
    {
        {x_scale * 1, y_scale * 1},
        {x_scale * 99,y_scale * 1},
        {x_scale * 99, y_scale * 79},
        {x_scale * 1, y_scale * 79}
    };
    painter->setBrush(Qt::white);
    painter->drawPolygon({polygon_shape}, Qt::WindingFill);

    painter->drawLine (QPointF {x_scale * 1, y_scale * 20}, {x_scale * 99, y_scale * 20});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 40}, {x_scale * 99, y_scale * 40});
    painter->drawLine (QPointF {x_scale * 1, y_scale * 59}, {x_scale * 99, y_scale * 59});
}

static void storage_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;

    QVector<QPointF> polygon_shape
    {
        {x_scale * 49, y_scale * 1},
        {x_scale * 99, y_scale * 79},
        {x_scale * 1, y_scale * 79}
    };
    painter->setBrush(Qt::white);
    painter->drawPolygon({polygon_shape}, Qt::WindingFill);

    QFont font;
    font.setPointSize(22);
    font.setBold(true);
    QFontMetricsF metrics (font);
    auto text_height = metrics.height();
    auto text_width = metrics.width("I");
    QRectF text_rect {x_scale * 49 - text_width/2,y_scale * 40, text_width,text_height};
    painter->setFont(font);
    painter->drawText(text_rect, "I", Qt::AlignVCenter | Qt::AlignCenter);
}

static void truck_transport_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * width);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;

    painter->setBrush(Qt::white);

    QVector<QPointF> polygon_shape
    {
        {x_scale * 1, y_scale * 1},
        {x_scale * 69, y_scale * 1},
        {x_scale * 69, y_scale * 55},
        {x_scale * 1, y_scale * 55}
    };
    painter->drawPolygon({polygon_shape}, Qt::WindingFill);

    polygon_shape.clear();
    polygon_shape = {
        {x_scale * 69, y_scale * 25},
        {x_scale * 99, y_scale * 25},
        {x_scale * 99, y_scale * 55},
        {x_scale * 69, y_scale * 55}
    };
    painter->drawPolygon({polygon_shape}, Qt::WindingFill);

    painter->setBrush(Qt::black);
    painter->drawEllipse (QPointF {x_scale * 17, y_scale * 65}, x_scale * 12, x_scale * 12);
    painter->drawEllipse (QPointF {x_scale * 72, y_scale * 65}, x_scale * 12, x_scale * 12);
}

static void storage_super_market_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * width);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;

    painter->drawLine (QPointF {x_scale * 29,y_scale * 1}, {x_scale * 71, y_scale * 1});
    painter->drawLine (QPointF {x_scale * 29,y_scale * 27}, {x_scale * 71, y_scale * 27});
    painter->drawLine (QPointF {x_scale * 29,y_scale * 53}, {x_scale * 71, y_scale * 53});
    painter->drawLine (QPointF {x_scale * 29, y_scale * 79}, {x_scale * 71, y_scale * 79});
    painter->drawLine (QPointF {x_scale * 71, y_scale * 1}, {x_scale * 71, y_scale * 79});
}

static void information_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setWidthF(0.02 * width);
    the_pen.setColor(Qt::black);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;
    QVector<QPointF> polygon_shape
    {
        {x_scale * 1,y_scale * 1},
        {x_scale * 99, y_scale * 1},
        {x_scale * 99,y_scale * 79},
        {x_scale * 1, y_scale * 79}
    };
    painter->setBrush (Qt::white);
    painter->drawPolygon ({polygon_shape}, Qt::WindingFill);
}

static void production_watcher_board_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setWidthF(0.02 * width);
    the_pen.setColor(Qt::black);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;
    QVector<QPointF> polygon_shape
    {
        {x_scale * 1,y_scale * 1},
        {x_scale * 85, y_scale * 1},
        {x_scale * 99, y_scale * 16},
        {x_scale * 99, y_scale * 79},
        {x_scale * 1, y_scale * 79},
    };
    painter->setBrush (Qt::white);
    painter->drawPolygon ({polygon_shape}, Qt::WindingFill);
}

static void material_fetch_watch_board_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setWidthF(0.02 * width);
    the_pen.setColor(Qt::black);
    painter->setPen(the_pen);

    auto x_scale = width / 100;
    auto y_scale = height / 80;

    QVector<QPointF> polygon_shape
    {
        {x_scale * 1,y_scale * 1},
        {x_scale * 85, y_scale * 1},
        {x_scale * 99, y_scale * 16},
        {x_scale * 99, y_scale * 79},
        {x_scale * 1, y_scale * 79},
    };
    painter->setBrush (Qt::white);
    painter->drawPolygon ({polygon_shape}, Qt::WindingFill);
    painter->drawLine (QPointF {x_scale * 1, y_scale * 39}, {x_scale * 25, y_scale * 1});
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
    the_pen.setWidthF(0.02 * width);
    painter->setPen(the_pen);

    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1, p2, p3}}, Qt::WindingFill);
}

static void sequence_pull_ball_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(0.02 * width);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
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

    auto font = painter->font();
    font.setBold(true);
    font.setPointSize (12);
    QFontMetricsF metrics (font);
    auto w = metrics.width("O X O X");
    auto h = metrics.height();

    auto center = rect.center();
    auto text_rect = QRectF (center.x() - 0.5 * w, center.y() - 0.5 * h, w, h);

    painter->setBrush(Qt::white);
    painter->drawRect(rect);

    painter->setFont(font);
    painter->drawText(text_rect,"O X O X", Qt::AlignVCenter | Qt::AlignCenter);
}

static void adjustment_on_scene_maker (QPainter* painter, qreal width, qreal height)
{
    auto x_scale = width / 100;
    auto y_scale = height / 80;

    QPointF
    p1 {42 * x_scale, 60 * y_scale},
    p2 {60 * x_scale, 60 * y_scale},
    p3 {22 * x_scale, 54 * y_scale},
    p4 {30 * x_scale, 20 * y_scale},
    p5 {33 * x_scale, 28 * y_scale},
    p6 {78 * x_scale, 53 * y_scale},
    p7 {82 * x_scale, 20 * y_scale},
    p8 {85 * x_scale, 28 * y_scale};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(width * 0.02);
    painter->setPen(the_pen);

    painter->setBrush(Qt::white);
    painter->drawEllipse(QRectF (20, 50, 22, 22));
    painter->drawEllipse(QRectF (60,50, 22, 22));

    painter->drawLine(p1,p2);
    painter->drawLine(p3,p4);
    painter->drawLine(p4,p5);
    painter->drawLine(p6,p7);
    painter->drawLine(p7,p8);

}

static void improvement_maker (QPainter* painter, qreal width, qreal height)
{
    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::red);
    the_pen.setWidthF(0.02 * width);
    painter->setPen(the_pen);
    painter->setBrush(Qt::white);
    auto x_scale = width / 100;
    auto y_scale = height / 80;

    QVector<QPointF> polygon_shape
    {
        {x_scale * 1,y_scale * 8},
        {x_scale * 33,y_scale * 23},
        {x_scale * 38, y_scale * 10},
        {x_scale * 49, y_scale * 21},
        {x_scale * 65, y_scale * 1},
        {x_scale * 64, y_scale * 19},
        {x_scale * 82, y_scale * 17},
        {x_scale * 76, y_scale * 26},
        {x_scale * 93, y_scale * 30},
        {x_scale * 80, y_scale * 37},
        {x_scale * 97, y_scale * 48},
        {x_scale * 77, y_scale * 47},
        {x_scale * 80, y_scale * 62},
        {x_scale * 64, y_scale * 53},
        {x_scale * 59, y_scale * 68},
        {x_scale * 48, y_scale * 55},
        {x_scale * 39, y_scale * 74},
        {x_scale * 35, y_scale * 57},
        {x_scale * 22, y_scale * 62},
        {x_scale * 25, y_scale * 51},
        {x_scale * 1, y_scale * 52},
        {x_scale * 17, y_scale * 42},
        {x_scale * 1, y_scale * 31},
        {x_scale * 20, y_scale * 27},
        {x_scale * 1, y_scale * 8}
    };

    painter->drawPolygon({polygon_shape}, Qt::WindingFill);
}

static void cache_or_safe_storage_maker (QPainter* painter, qreal width, qreal height)
{
    auto x_scale = width / 100;
    auto y_scale = height / 80;
    QPointF
            p1 {x_scale * 39, y_scale * 1},
    p2 {x_scale * 60, y_scale * 1},
    p4 {x_scale * 60, y_scale * 79},
    p3 {x_scale * 39, y_scale * 79},
    p5 {x_scale * 39, y_scale * 27},
    p6 {x_scale * 60, y_scale * 27},
    p7 {x_scale * 39, y_scale * 53},
    p8 {x_scale * 60, y_scale * 53};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(width/50);
    painter->setPen(the_pen);

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

    painter->setBrush(Qt::white);
    painter->drawEllipse (QRectF(0.3 * width, height * 20 / 80, 0.4 * width, height * 40 / 80));
}

static void fetch_material_maker (QPainter* painter, qreal width, qreal height)
{
    QPointF
    p1 {0.75 * width, 0.76 * height},
    p2 {0.82 * width, 0.9 * height},
    p3 {0.86 * width,0.65 * height};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(width / 50);
    painter->setPen(the_pen);


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

    painter->drawText(text_rect, "FIFO");
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
    auto x_scale = width / 100;
    auto y_scale = height / 80;

    auto the_pen = painter->pen ();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(x_scale * 2);
    painter->setPen(the_pen);

    QPointF p1 (1 * x_scale, 32 * y_scale);
    QPointF p2 (82 * x_scale, 32 * y_scale);
    QPointF p3 (82 * x_scale, 24 * y_scale);
    QPointF p4 (99 * x_scale, 40 * y_scale);
    QPointF p5 (82 * x_scale, 56 * y_scale);
    QPointF p6 (82 * x_scale, 48 * y_scale);
    QPointF p7 (1 * x_scale, 48 * y_scale);

    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1, p2, p3, p4, p5, p6, p7}} , Qt::WindingFill);
}

static void tradition_info_flow_maker(QPainter* painter, qreal width, qreal height)
{
    auto x_scale = width / 100;
    auto y_scale = height / 80;
    QPointF p1{90 * x_scale, 41 * y_scale},
    p2{19 * x_scale ,41 * y_scale},
    p3{19 * x_scale,38 * y_scale},
    p4{19 * x_scale,44 * y_scale},
    p5{13 * x_scale,41 * y_scale};
    auto the_pen = painter->pen();
    the_pen.setWidthF(2.0);
    the_pen.setColor(Qt::blue);
    painter->setPen(the_pen);
    painter->drawLine(p1,p2);
    painter->setBrush(Qt::blue);
    painter->drawPolygon({{p3,p4,p5}},Qt::WindingFill);

}
static void electric_info_flow_maker(QPainter* painter,qreal width,qreal height)
{
    auto x_scale = width /100;
    auto y_scale = height /80;

    QPointF p1 {93 * x_scale, 24 * y_scale},
    p2{53 * x_scale, 18 * y_scale},
    p3{58 * x_scale, 26 * y_scale},
    p4{16 * x_scale, 20 * y_scale},
    p5{16 * x_scale, 17 * y_scale},
    p6{15 * x_scale, 22 * y_scale},
    p7 {1 * x_scale, 18 * y_scale};

    auto the_pen = painter->pen();
    the_pen.setWidthF(2.0);
    the_pen.setColor(Qt::blue);
    painter->setPen(the_pen);
    painter->setBrush(Qt::blue);
    painter->drawLine(p1,p2);
    painter->drawLine(p2,p3);
    painter->drawLine(p3,p4);
    painter->drawPolygon({{p5,p6,p7}},Qt::WindingFill);

}
static void board_info_flow_maker(QPainter* painter, qreal width,qreal height)
{
    auto x_scale = width / 100;
    auto y_scale = height / 80;
    QPointF p1{91 * x_scale, 18 * y_scale},
    p2{15 * x_scale, 18 * y_scale},
    p3{15 * x_scale, 59 * y_scale},
    p4{12 * x_scale, 59 * y_scale},
    p5{18 * x_scale, 59 * y_scale},
    p6{15 * x_scale, 65* y_scale};
    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setBrush(Qt::black);
    painter->drawPolygon({{p4,p5,p6}},Qt::WindingFill);
    the_pen.setStyle(Qt::DashLine);
    painter->setPen(the_pen);
    painter->drawLine(p1,p2);
    painter->drawLine(p2,p3);
}
static void material_flow_maker(QPainter* painter,qreal width, qreal height)
{
    qDebug() << "qdebug";
    auto x_scale = width / 100;
    auto y_scale = height / 80;

    QPointF p1{34 * x_scale, 51 * y_scale },
    p2{34 * x_scale, 61 * y_scale},
    p3{ 41 * x_scale, 61 * y_scale},
    p4{41 * x_scale, 51 * y_scale},

    p5{49 * x_scale,51 * y_scale},
    p6{49 * x_scale, 61 * y_scale},

    p7{56 * x_scale,51 * y_scale},
    p8{56* x_scale,61 * y_scale},

    p9{65 * x_scale,51 * y_scale},
    p10 {65 * x_scale,61 * y_scale},

    p11{73 * x_scale, 51 * y_scale},
    p12{73 * x_scale, 61* y_scale},

    p13{81 * x_scale,51 * y_scale},
    p14{81 * x_scale,61 * y_scale},

    p15{81 * x_scale,  46 * y_scale},
    p16{81 * x_scale, 66 * y_scale},
    p17{91 * x_scale, 56 * y_scale};

    auto the_pen = painter->pen();
    the_pen.setColor(Qt::black);
    the_pen.setWidthF(2.0);
    painter->setPen(the_pen);

    painter->setBrush(Qt::white);
    painter->drawPolygon({{p1,p2,p3,p4}},Qt::WindingFill);

    painter->setBrush(Qt::black);
    painter->drawPolygon({{p3,p4,p5,p6}},Qt::WindingFill);

    painter->setBrush(Qt::white);
    painter->drawPolygon({{p5,p6,p8,p7}},Qt::WindingFill);

    painter->setBrush(Qt::black);
    painter->drawPolygon({{p7,p8,p10,p9}});

    painter->setBrush(Qt::white);
    painter->drawPolygon({{p9,p10,p12,p11}},Qt::WindingFill);
    painter->drawPolygon({{p15,p16,p17}},Qt::WindingFill);

    painter->setBrush(Qt::black);
    painter->drawPolygon({{p11,p12,p14,p13}},Qt::WindingFill);

}

%>
