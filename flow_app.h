﻿#pragma once

#include "qt-tools/application.h"

class flow_app : public application
{
public:
    flow_app(int argc, char** argv);
    bool run () override;
};

