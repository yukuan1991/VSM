#ifndef FLOW_MAIN_H
#define FLOW_MAIN_H

#include <QMainWindow>

namespace Ui {
class flow_main;
}

class flow_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit flow_main(QWidget *parent = 0);
    ~flow_main();

private:
    Ui::flow_main *ui;
};

#endif // FLOW_MAIN_H
