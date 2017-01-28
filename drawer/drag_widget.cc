#include "drag_widget.h"
#include <QMouseEvent>
#include "utility/raii.hpp"
#include <QLabel>
#include <QDrag>
#include <QMimeData>

namespace drawer {

drag_widget::drag_widget(QWidget *parent) : QWidget(parent)
{

}

void drag_widget::mousePressEvent(QMouseEvent *event)
{
    SCOPE_EXIT { QWidget::mousePressEvent(event); };
    auto pos = event->pos ();
    auto child = childAt(pos);

    if (child == nullptr)
    {
        return;
    }

    auto label = dynamic_cast<QLabel*>(child);
    if (label == nullptr)
    {
        return;
    }

    if (label->objectName().isEmpty())
    {
        return;
    }

    auto pm = label->pixmap();


    QDrag drag (this);
    auto data = std::make_unique<QMimeData> ();
    {
        auto str = label->objectName().toStdString();
        data->setData ("item", QByteArray (str.data(), static_cast<int> (str.size())));
    }
    drag.setMimeData (data.release ());
    drag.setPixmap (*pm);
    drag.setHotSpot ({pm->width () / 2, pm->height () / 2});

    drag.exec (Qt::CopyAction);
}

} // namespace drawer
