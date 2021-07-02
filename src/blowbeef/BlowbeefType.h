#pragma once
#include <iostream>
#include <vector>


enum class BlowbeefOutputType
{
	CSV,
	HTML,
	LOG
};

struct TableData
{
	int FieldsNum;
	int RowsNum;
	std::vector<std::string> Fields;
	std::vector<std::vector<std::string>> Data;
    std::string Description;
};



enum class ModuleType
{
    All,
    PROCESS,
    DNS_Cache,
    Net_Route,
    Net_IPAddress,
    Net_TCPConnection,
    DISK_Volume,
    PRODUCT,
    QUICK_FIX_ENGINEERING,
};


