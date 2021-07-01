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
	std::string Description;
	int FieldsNum;
	int RowsNum;
	std::vector<std::string> Fields;
	std::vector<std::vector<std::string>> Data;
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


std::map<std::string, ModuleType> ModuleMap{
        {"All", ModuleType::All},
        {"Process", ModuleType::PROCESS},
        {"DNS_Cache", ModuleType::DNS_Cache} ,
        {"Product", ModuleType::PRODUCT} ,
        {"Net_Route", ModuleType::Net_Route} ,
        {"Net_IPAddress", ModuleType::Net_IPAddress} ,
        {"Net_TCPConnection", ModuleType::Net_TCPConnection} ,
        {"DISK_Volume", ModuleType::DISK_Volume} ,
        {"Quick_Fix", ModuleType::QUICK_FIX_ENGINEERING}
};