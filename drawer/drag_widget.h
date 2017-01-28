#ifndef DRAWER_DRAG_WIDGET_H
#define DRAWER_DRAG_WIDGET_H

#include <QWidget>

namespace drawer {

class drag_widget : public QWidget
{
    Q_OBJECT
public:
    explicit drag_widget(QWidget *parent = 0);

signals:

public slots:
};

} // namespace drawer

#endif // DRAWER_DRAG_WIDGET_H