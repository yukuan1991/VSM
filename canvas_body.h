#ifndef CANVAS_BODY_H
#define CANVAS_BODY_H

#include "canvas_view.h"
#include "canvas_scene.h"

class canvas_body : public canvas_view
{
public:
    canvas_body(QWidget* parent = nullptr);
private:
    canvas_scene scene_;
};

#endif // CANVAS_BODY_H
