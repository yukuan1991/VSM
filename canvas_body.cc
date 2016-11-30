#include "canvas_body.h"

canvas_body::canvas_body(QWidget *parent)
    :canvas_view (parent)
{
    setScene (&scene_);
}
