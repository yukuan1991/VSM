#include "flow_main.h"
#include "ui_flow_main.h"

flow_main::flow_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::flow_main)
{
    ui->setupUi(this);

}

flow_main::~flow_main()
{
    delete ui;
}
