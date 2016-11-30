#include "drawer_list.h"
#include <assert.h>
#include <QMouseEvent>
#include <QSvgWidget>
#include <QSvgRenderer>
#include <QFileInfo>
#include <QPainter>
#include <QDrag>
#include <QMimeData>
#include <QDebug>


drawer_list::drawer_list(QWidget *parent)
        :QListWidget (parent)
{
    setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    set_data ({});
}

void drawer_list::set_data(const QStringList& data)
{
    for (auto & it : data)
    {
        auto new_item = std::make_unique<QListWidgetItem> ();
        auto raw_item = new_item.get ();
        raw_item->setFlags (new_item->flags () & (~ Qt::ItemIsSelectable));


        QByteArray arr (it.toUtf8 ());
        qDebug () << QString (arr);

        raw_item->setData (path_role, arr);

        addItem (new_item.release ());

        auto svg_item = std::make_unique<QSvgWidget> (it, this);
        raw_item->setSizeHint ({50, 50});
        raw_item->setToolTip (QFileInfo (it).baseName ());
        setItemWidget (raw_item, svg_item.release ());
    }

}

void drawer_list::mousePressEvent(QMouseEvent *event)
{
    auto pos = event->pos ();

    auto item = itemAt (pos);

    if (item == nullptr)
    {
        return;
    }

    auto widget = itemWidget (item);
    auto svg_widget = dynamic_cast<QSvgWidget*>(widget);

    if (svg_widget == nullptr)
    {
        return;
    }

    auto renderer = svg_widget->renderer ();
    if (renderer == nullptr)
    {
        return;
    }

    auto size = renderer->defaultSize ();

    QPixmap pm(size.width (), size.height ());
    pm.fill (Qt::transparent);
    QPainter painter(&pm);

    renderer->render(&painter);

    QDrag drag (this);
    auto data = std::make_unique<QMimeData> ();
    data->setData ("svg", item->data (path_role).toByteArray ());
    drag.setMimeData (data.release ());
    drag.setPixmap (pm);
    drag.setHotSpot ({pm.width () / 2, pm.height () / 2});

    drag.exec (Qt::CopyAction);
}
