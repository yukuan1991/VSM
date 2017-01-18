#include "remark_widget.h"
#include "ui_remark_widget.h"

remark_widget::remark_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::remark_widget)
{
    ui->setupUi(this);
    init_conn();
}

remark_widget::~remark_widget()
{
    delete ui;
}

void remark_widget::set_remark(const QString &remark)
{
    ui->edit_remark->setText (remark);
}

QString remark_widget::remark()
{
    return ui->edit_remark->toPlainText();
}

void remark_widget::init_conn()
{
    connect(ui->edit_remark, &QTextEdit::textChanged, [this] { emit text_changed (); });
}
