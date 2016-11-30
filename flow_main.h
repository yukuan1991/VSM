#ifndef FLOW_MAIN_H
#define FLOW_MAIN_H

#include <QMainWindow>
#include <QDockWidget>
#include <memory>

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

private:
    Ui::flow_main *ui;
    std::unique_ptr<QDockWidget> drawer_ = std::make_unique<QDockWidget> (this);
};

#endif // FLOW_MAIN_H
