#pragma once

#include <QGraphicsScene>
#include "utility/interface.hpp"
#include <QGraphicsSvgItem>


QGraphicsSvgItem* add_svg_to_scene (const QString& path, not_null<QGraphicsScene*> scene, QPointF pos);

qreal distance (QPointF p1, QPointF p2);
