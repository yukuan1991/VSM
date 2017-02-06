#include "drag_widget.h"
#include <QMouseEvent>
#include "utility/raii.hpp"
#include "item/item.h"
#include <QLabel>
#include <QDrag>
#include <QMimeData>
#include "drawer/drag_pixmap.h"

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

    auto object_name = label->objectName();
    if (object_name.isEmpty())
    {
        return;
    }

    auto pm = drawer::make_pixmap(object_name, 100, 80);


    QDrag drag (this);
    auto data = std::make_unique<QMimeData> ();
    {
        auto str = label->objectName().toStdString();
        data->setData ("item", QByteArray (str.data(), static_cast<int> (str.size())));
    }

    drag.setMimeData (data.release ());
    drag.setPixmap (pm);
    drag.setHotSpot ({pm.width () / 2, pm.height () / 2});

    drag.exec (Qt::CopyAction);
}

} // namespace drawer
