#pragma once

#include <QWidget>
#include "utility/memory.hpp"
#include "utility/containers.hpp"

class QPushButton;
namespace drawer {
using std::unique_ptr;
using std::make_unique;

class drag_widget final: public QWidget
{
    Q_OBJECT
signals:
    void button_triggered (const QString&);
public:
    static unique_ptr<drag_widget> make (vector<QString> labels = {},
                                         vector<QString> buttons = {},
                                         QWidget* parent = nullptr);
    bool init ();
    void reset_status ();
    ~drag_widget ();
private:
    explicit drag_widget(vector<QString> labels = {},
                         vector<QString> buttons = {},
                         QWidget *parent = nullptr);
    void on_button_pressed ();
    void hideEvent (QHideEvent* event) override;

    /// events
    void mousePressEvent (QMouseEvent* event) override;

private:
    vector<QString> label_names_;
    vector<QString> button_names_;
    vector<QPushButton*> buttons_;
};

} // namespace drawer

