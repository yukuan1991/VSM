#ifndef REMARK_WIDGET_H
#define REMARK_WIDGET_H

#include <QWidget>

namespace Ui {
class remark_widget;
}

class remark_widget : public QWidget
{
    Q_OBJECT

public:
    explicit remark_widget(QWidget *parent = 0);
    ~remark_widget();
    void set_remark (const QString& remark);
    QString remark ();
signals:
    void text_changed ();
private:
    void init_conn ();
private:
    Ui::remark_widget *ui;
};

#endif // REMARK_WIDGET_H
