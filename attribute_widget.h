#ifndef ATTRIBUTE_WIDGET_H
#define ATTRIBUTE_WIDGET_H

#include <QWidget>
#include <memory>
#include "json.hpp"
///属性类
class attribute_widget final : public QWidget
{
    Q_OBJECT
public:
    std::unique_ptr<attribute_widget> make (nlohmann::json data, QWidget* parent = nullptr);
    ~attribute_widget () override;
private:
    explicit attribute_widget(QWidget *parent = 0);
    bool init ();
private:
    nlohmann::json data_;
};

#endif // ATTRIBUTE_WIDGET_H
