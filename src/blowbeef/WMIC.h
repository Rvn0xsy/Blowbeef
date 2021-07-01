#pragma once
#define _WIN32_DCOM
#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#include <easylogging++.h>
#include <comutil.h>
#include <locale>
#include <codecvt>
#include "BlowbeefType.h"


#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "comsupp.lib")

struct WMI_STRUCT {
    HRESULT hres;
    IEnumWbemClassObject* pEnumerator = NULL;
    IWbemLocator* pLoc = NULL;
    IWbemServices* pSvc = NULL;
    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
};



class WMIQueryer {
public:
    WMIQueryer();
    BOOL OpenNamespace(std::string NameSpacePath);
    BOOL WMIQuery(std::string QueryStr);
    BOOL WMIShowData(std::vector<std::string> Fields);
    BOOL WMIShowTableData(TableData* Data);
    TableData * WMIGetData(std::vector<std::string> Fields, TableData * Data);
    VOID Release();
    ~WMIQueryer();
private:
    struct WMI_STRUCT* WmiObj;
};
