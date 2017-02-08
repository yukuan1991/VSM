#include "attribute_widget.h"
#include "utility/raii.hpp"
#include <QGridLayout>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QLineEdit>

std::unique_ptr<attribute_widget> attribute_widget::make(nlohmann::json data, QWidget *parent)
{
    auto ret = std::unique_ptr<attribute_widget> (new attribute_widget (::move (data), parent));
    if (!ret->init())
    {
        return nullptr;
    }

    return ret;
}

attribute_widget::~attribute_widget()
{

}

attribute_widget::attribute_widget(nlohmann::json data, QWidget *parent) :
    QWidget(parent),
    data_ (::move (data))
{

}

bool attribute_widget::init() try
{
    auto layout = new QGridLayout (this);

    int i = 0;
    for (auto & it : data_)
    {
        std::string key = it.begin().key();
        std::string value = it.begin().value();

        layout->addWidget(new QLabel (key.data (), this), i, 0);

        auto edit = std::make_unique<QLineEdit> (value.data (), this);
        connect(edit.get(), &QLineEdit::textChanged, [this, key = key] (auto&& text)
        {
            changed_values_ [key] = text.toStdString ();
        });

        layout->addWidget(edit.release (), i, 1);
        SCOPE_EXIT { i++; };
    }

    auto button_commit = std::make_unique<QPushButton> ("提交", this);
    connect (button_commit.get (), &QPushButton::clicked, this, &attribute_widget::commit);
    layout->addWidget(button_commit.release(), i, 1);
    i ++;
    layout->addItem (new QSpacerItem (0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), i, 1);

    return true;
}
catch (const std::exception& e)
{
    Q_UNUSED (e);
    return false;
}
