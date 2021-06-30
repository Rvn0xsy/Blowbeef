#pragma once
#include "modules.h"
class Product :
    public Modules
{
public:
    Product(std::string tomlConfigFile);
    VOID HandleData();
};

