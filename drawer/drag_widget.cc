#include "drag_widget.h"
#include <QMouseEvent>
#include <QLabel>
#include <QDrag>
#include <QMimeData>
#include <QVBoxLayout>
#include <QPushButton>

#include "utility/raii.hpp"
#include "item/maker.hpp"
#include "drawer/drag_pixmap.h"


namespace drawer {


drag_widget::drag_widget(std::vector<QString> labels, std::vector<QString> buttons, QWidget *parent)
    : QWidget(parent)
    , label_names_ (::move (labels))
    , button_names_ (::move (buttons))
{

}

void drag_widget::on_button_pressed()
{
    qDebug () << "button pressed";
    auto button = dynamic_cast<QPushButton*>(sender ());
    if (button == nullptr)
    {
        return;
    }
    auto name = button->objectName();

    if (name.isEmpty())
    {
        return;
    }

    ///
    if (button->isChecked())
    {
        for (auto it : buttons_)
        {
            if (it != button)
            {
                it->setChecked (false);
            }
        }
        emit button_triggered(name);
    }
    else
    {
        emit button_triggered("");
    }
}

void drag_widget::hideEvent(QHideEvent *event)
{
    SCOPE_EXIT { QWidget::hideEvent (event); };

    for (auto it : buttons_)
    {
        it->setChecked(false);
    }
    emit button_triggered("");
}

unique_ptr<drag_widget> drag_widget::make(vector<QString> labels, vector<QString> buttons, QWidget *parent)
{
    std::unique_ptr<drag_widget> ret (new drag_widget (::move (labels), ::move (buttons), parent));
    if (ret != nullptr and ret->init())
    {
        return ret;
    }
    else
    {
        return nullptr;
    }
}

bool drag_widget::init()
{
    auto v_layout = new QVBoxLayout(this);

    for (auto & it : label_names_)
    {
        auto map = drawer::make_pixmap (it, 100, 80);

        auto pic_label = new QLabel (this);
        pic_label->setObjectName(it);
        pic_label->setPixmap(map.scaled(100, 80));
        v_layout->addWidget (pic_label);

        auto info_label = new QLabel (it, this);
        v_layout->addWidget (info_label);
    }

    buttons_.reserve(button_names_.size ());
    for (auto & it : button_names_)
    {
        auto button = new QPushButton (drawer::make_pixmap(it, 100, 80), "", this);
        button->setObjectName(it);
        button->setIconSize({100, 80});
        button->setCheckable(true);
        button->setChecked(false);

        connect (button, &QPushButton::clicked, this, &drag_widget::on_button_pressed);
        v_layout->addWidget(button);
        buttons_.emplace_back (button);

        auto info_label = std::make_unique<QLabel> (it, this);
        info_label->setAlignment(Qt::AlignHCenter);
        v_layout->addWidget (info_label.release());
    }

    v_layout->addItem (new QSpacerItem (0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    return true;
}

drag_widget::~drag_widget()
{

}

void drag_widget::mousePressEvent(QMouseEvent *event)
{
    SCOPE_EXIT { QWidget::mousePressEvent(event); };
    auto pos = event->pos ();
    auto child = childAt(pos);

    if (child == nullptr)
    {
        return;
    }

    auto label = dynamic_cast<QLabel*>(child);
    if (label == nullptr)
    {
        return;
    }

    auto object_name = label->objectName();
    if (object_name.isEmpty())
    {
        return;
    }

    auto pm = drawer::make_pixmap(object_name, 100, 80);


    QDrag drag (this);
    auto data = std::make_unique<QMimeData> ();
    {
        auto str = label->objectName().toStdString();
        data->setData ("item", QByteArray (str.data(), static_cast<int> (str.size())));
    }

    drag.setMimeData (data.release ());
    drag.setPixmap (pm);
    drag.setHotSpot ({pm.width () / 2, pm.height () / 2});

    drag.exec (Qt::CopyAction);
}

} // namespace drawer
