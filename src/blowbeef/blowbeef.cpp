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
#include "BlowbeefOutput.h"

INITIALIZE_EASYLOGGINGPP


int main(int argc, char** argv)
{

    CLI::App app{ "BlowBeef is a tool for analyzing WMI data. @Rvn0xsy" };

    // std::string tomlConfigFile = "./blowbeef.toml";
    std::string outputFile = "./output.html";
   
    ModuleType moduleType;
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
    // app.add_option("-f,--file", tomlConfigFile, "Analysis rules file.")->check(CLI::ExistingFile);
    app.add_option("-o,--output", outputFile, "Output file.")->required();
    
    app.add_option("-m,--modules", moduleType, "Module name.")->required()->transform(CLI::CheckedTransformer(ModuleMap, CLI::ignore_case));
    
    CLI11_PARSE(app, argc, argv);
    BlowbeefOutput OutPuter(outputFile, BlowbeefOutputType::JSON);

    Process* Pr = new Process();
    DNS_Cache* DnsCache = new DNS_Cache();
    NetRoute * Net_Route = new NetRoute();
    IPAddress* Net_IPAddress = new IPAddress();
    NetTCPConnection* Net_TCPConnection = new NetTCPConnection();
    DISK_Volume* Disk_Volume = new DISK_Volume();
    Product* Win32_Product = new Product();
    QuickFixEngineering* Win32QuickFix = new QuickFixEngineering();

    switch (moduleType)
    {
    case ModuleType::All:
        Pr->Query();
        if (outputFile != "") {
            OutPuter << Pr->GetData();
        }
        Pr->Release();
        DnsCache->Query();
        if (outputFile != "") {
            OutPuter << DnsCache->GetData();
        }
        DnsCache->Release();
        Win32_Product->Query();
        if (outputFile != "") {
            OutPuter << Win32_Product->GetData();
        }
        Win32_Product->Release();
        Net_Route->Query();
        if (outputFile != "") {
            OutPuter << Net_Route->GetData();
        }
        Net_Route->Release();
        Net_IPAddress->Query();
        if (outputFile != "") {
            OutPuter << Net_IPAddress->GetData();
        }
        Net_IPAddress->Release();
        Net_TCPConnection->Query();
        if (outputFile != "") {
            OutPuter << Net_TCPConnection->GetData();
        }
        Net_TCPConnection->Release();
        Disk_Volume->Query();
        if (outputFile != "") {
            OutPuter << Disk_Volume->GetData();
        }
        Disk_Volume->Release();
        Win32QuickFix->Query();
        if (outputFile != "") {
            OutPuter << Win32QuickFix->GetData();
        }
        Win32QuickFix->Release();
        break;
    case ModuleType::PROCESS:
        Pr->Query();
        if (outputFile != "") {
            OutPuter << Pr->GetData();
        }
        break;
    case ModuleType::DNS_Cache:
        DnsCache->Query();
        if (outputFile != "") {
            OutPuter << DnsCache->GetData();
        }
        DnsCache->Release();
        break;
    case ModuleType::PRODUCT:
        Win32_Product->Query();
        if (outputFile != "") {
            OutPuter << Win32_Product->GetData();
        }
        
        Win32_Product->Release();
        break;
    case ModuleType::Net_Route:
        Net_Route->Query();
        if (outputFile != "") {
            OutPuter << Net_Route->GetData();
        }
        Net_Route->Release();
        break;
    case ModuleType::Net_IPAddress:
        Net_IPAddress->Query();
        if (outputFile != "") {
            OutPuter << Net_IPAddress->GetData();
        }
        Net_IPAddress->Release();
        break;
    case ModuleType::Net_TCPConnection:
        Net_TCPConnection->Query();
        if (outputFile != "") {
            OutPuter << Net_TCPConnection->GetData();
        }
        Net_TCPConnection->Release();
        break;
    case ModuleType::DISK_Volume:
        Disk_Volume->Query();
        if (outputFile != "") {
            OutPuter << Disk_Volume->GetData();
        }
        Disk_Volume->Release();
        break;
    case ModuleType::QUICK_FIX_ENGINEERING:
        Win32QuickFix->Query();
        if (outputFile != "") {
            OutPuter << Win32QuickFix->GetData();
        }
        Win32QuickFix->Release();
        break;
    default:
        break;
    }
   

    return 0;
   
}
