// blowbeef.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <CLI/CLI.hpp>
#include "process.h"
#include "DNS_Cache.h"
#include "NetRoute.h"
#include "IPAddress.h"
#include "NetTCPConnection.h"
#include "Disk_Volume.h"
#include "Product.h"
#include "QuickFixEngineering.h"

INITIALIZE_EASYLOGGINGPP

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

int main(int argc, char** argv)
{

    CLI::App app{ "BlowBeef is a tool for analyzing WMI data. @Rvn0xsy" };

    std::string tomlConfigFile = "./blowbeef.toml";
    std::string outputFile = "./output.log";
   // ModuleType moduleType = All;
    std::map<std::string, ModuleType> map{ 
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

    ModuleType moduleType;
    app.add_option("-f,--file", tomlConfigFile, "Analysis rules file.")->check(CLI::ExistingFile);
    app.add_option("-o,--output", outputFile, "Output file.");
    
    app.add_option("-m,--modules", moduleType, "Module name.")->required()->transform(CLI::CheckedTransformer(map, CLI::ignore_case));;
    
    CLI11_PARSE(app, argc, argv);
    
    Process* Pr = new Process(tomlConfigFile);
    DNS_Cache* DnsCache = new DNS_Cache(tomlConfigFile);
    NetRoute * Net_Route = new NetRoute(tomlConfigFile);
    IPAddress* Net_IPAddress = new IPAddress(tomlConfigFile);
    NetTCPConnection* Net_TCPConnection = new NetTCPConnection(tomlConfigFile);
    DISK_Volume* Disk_Volume = new DISK_Volume(tomlConfigFile);
    Product* Win32_Product = new Product(tomlConfigFile);
    QuickFixEngineering* Win32QuickFix = new QuickFixEngineering(tomlConfigFile);

    switch (moduleType)
    {
    case ModuleType::All:
        Pr->Query();
        Pr->HandleData();
        Pr->Release();
        DnsCache->Query();
        DnsCache->HandleData();
        DnsCache->Release();
        Win32_Product->Query();
        Win32_Product->HandleData();
        Win32_Product->Release();
        Net_Route->Query();
        Net_Route->HandleData();
        Net_Route->Release();
        Net_IPAddress->Query();
        Net_IPAddress->HandleData();
        Net_IPAddress->Release();
        Net_TCPConnection->Query();
        Net_TCPConnection->HandleData();
        Net_TCPConnection->Release();
        Disk_Volume->Query();
        Disk_Volume->HandleData();
        Disk_Volume->Release();
        Win32QuickFix->Query();
        Win32QuickFix->HandleData();
        Win32QuickFix->Release();
        break;
    case ModuleType::PROCESS:
        Pr->Query();
        Pr->HandleData();
        break;
    case ModuleType::DNS_Cache:
        DnsCache->Query();
        DnsCache->HandleData();
        break;
    case ModuleType::PRODUCT:
        Win32_Product->Query();
        Win32_Product->HandleData();
        break;
    case ModuleType::Net_Route:
        Net_Route->Query();
        Net_Route->HandleData();
        break;
    case ModuleType::Net_IPAddress:
        Net_IPAddress->Query();
        Net_IPAddress->HandleData();
        break;
    case ModuleType::Net_TCPConnection:
        Net_TCPConnection->Query();
        Net_TCPConnection->HandleData();
        break;
    case ModuleType::DISK_Volume:
        Disk_Volume->Query();
        Disk_Volume->HandleData();
        break;
    case ModuleType::QUICK_FIX_ENGINEERING:
        Win32QuickFix->Query();
        Win32QuickFix->HandleData();
        break;
    default:
        break;
    }
   

    return 0;
   
}
