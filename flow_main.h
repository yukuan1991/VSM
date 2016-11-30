#ifndef FLOW_MAIN_H
#define FLOW_MAIN_H

#include <QMainWindow>
#include <QDockWidget>
#include <memory>
#include "drawer_list.h"

namespace Ui {
class flow_main;
}

class flow_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit flow_main(QWidget *parent = 0);
    void set_drawer (const QStringList& data);
    ~flow_main();

private slots:
    void on_drawer_visibility_changed ();

    void on_action_drawer_triggered();

private:
    Ui::flow_main *ui;
    std::unique_ptr<QDockWidget> drawer_ = std::make_unique<QDockWidget> (this);
    std::unique_ptr<drawer_list> drawer_content_ = std::make_unique<drawer_list> (drawer_.get ());
};

#endif // FLOW_MAIN_H
