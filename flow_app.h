#pragma once

#include "qt-tools/application.h"
#include <flow_main.h>

class flow_app : public application
{
public:
    flow_app(int argc, char** argv);
    bool run () override;
private:
    std::unique_ptr<flow_main> main_;
};

