#pragma once

#include <QWidget>
#include <memory>
#include <utility>
#include <vector>
#include "json.hpp"
///属性类
class QPushButton;
class attribute_widget final : public QWidget
{
    Q_OBJECT
signals:
    void commit ();
public:
    using attributes = std::map<std::string, std::string>;
    static std::unique_ptr<attribute_widget> make (nlohmann::json data, QWidget* parent = nullptr);
    ~attribute_widget () override;
    const attributes& apply () const { return changed_values_; }
    void keyPressEvent (QKeyEvent* event) override;
private:
    explicit attribute_widget(nlohmann::json data, QWidget *parent = 0);
    bool init ();

private:
    const nlohmann::json data_;
    attributes changed_values_;
    QPushButton* button_commit_ = nullptr;
};

