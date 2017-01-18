#include "info_flow.h"
#include "ui_info_flow.h"
#include <assert.h>
#include <QDebug>
#include <QSpacerItem>
#include <QHideEvent>

using std::begin;
using std::end;
using std::find_if;

namespace drawer
<%

std::unique_ptr<info_flow> info_flow::make(QWidget *parent, const std::initializer_list<QString> &buttons)
{
    auto instance = std::unique_ptr<info_flow> (new info_flow (parent));
    if (!instance->init(buttons))
    {
        return nullptr;
    }
    else
    {
        return instance;
    }
}

QString info_flow::status()
{
    auto pressed = find_if (begin (buttons_), end (buttons_), [](auto && b) { return b->isChecked (); });
    if (pressed == end (buttons_))
    {
        return {};
    }
    else
    {
        return (*pressed)->text();
    }
}

bool info_flow::set_status(const QString& status)
{
    if (status.isEmpty ())
    {
        for (auto & it : buttons_)
        {
            it->setChecked(false);
        }
        return true;
    }


    auto selected = find_if (begin (buttons_), end (buttons_),
                             [&] (auto && b) { return b->text () == status; });

    if (selected == buttons_.end())
    {
        return false;
    }

    auto but = *selected;
    but->setChecked(true);
    return true;
}

bool info_flow::init(const std::initializer_list<QString> &buttons) try
{
    auto v_layout = new QVBoxLayout(this);

    buttons_.reserve(buttons.size());
    for (auto & it : buttons)
    {
        auto button = std::make_unique<QPushButton> (this);
        button->setText(it);
        buttons_.push_back(button.get ());

        button->setCheckable(true);
        button->setChecked(false);

        connect(button.get(), &QPushButton::clicked, this, &info_flow::button_clicked);

        v_layout->addWidget(button.release());
    }

    v_layout->addItem (new QSpacerItem (0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    return true;
}
catch (...)
{
    return false;
}

info_flow::info_flow(QWidget *parent) :
    QWidget(parent)
{
}

void info_flow::hideEvent(QHideEvent *event)
{
    for (auto & button : buttons_)
    {
        button->setChecked(false);
    }
    emit status_changed ("");
    QWidget::hideEvent(event);
}

void info_flow::button_clicked()
{
    auto src = sender (); assert (src);
    auto clicked = dynamic_cast<QPushButton*>(src); assert (clicked);

    for (auto & button : buttons_)
    {
        if (button != clicked)
        {
            button->setChecked(false);
        }
    }

    emit status_changed (clicked->isChecked() ? clicked->text() : "");
}

info_flow::~info_flow() {  }


%>
