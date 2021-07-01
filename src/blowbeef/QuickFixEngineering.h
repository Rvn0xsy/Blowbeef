#pragma once
#include "modules.h"
class QuickFixEngineering :
    public Modules
{

public:
    QuickFixEngineering(std::string tomlConfigFile);
    VOID HandleData();
};

