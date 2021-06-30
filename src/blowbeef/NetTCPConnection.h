#pragma once
#include "modules.h"
class NetTCPConnection :
    public Modules
{
public:
    NetTCPConnection(std::string tomlConfigFile);
    VOID HandleData();
};

