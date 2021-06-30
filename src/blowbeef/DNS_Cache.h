#pragma once
#include "modules.h"
class DNS_Cache : public Modules
{
public:
	DNS_Cache(std::string tomlConfigFile);
	VOID HandleData();
};

