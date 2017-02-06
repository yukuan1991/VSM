#include "attribute_widget.h"
#include "utility/raii.hpp"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

std::unique_ptr<attribute_widget> attribute_widget::make(nlohmann::json data, QWidget *parent)
{
    auto ret = std::unique_ptr<attribute_widget> (new attribute_widget (parent));
    ret->data_ = ::move (data);
    if (!ret->init())
    {
        return nullptr;
    }

    return ret;
}

attribute_widget::~attribute_widget()
{

}

attribute_widget::attribute_widget(QWidget *parent) : QWidget(parent)
{

}

bool attribute_widget::init() try
{
    auto layout = new QGridLayout (this);

    int i;
    for (auto it = data_.begin (); it != data_.end (); ++ it)
    {
        SCOPE_EXIT { i++; };
        std::string key = it.key ();
        std::string value = it.value ();
        layout->addWidget(new QLabel (key.data (), this), i, 0);
        layout->addWidget(new QLineEdit (value.data (), this), i, 1);
    }

    return true;
}
catch (const std::exception& e)
{
    Q_UNUSED (e);
    return false;
}
