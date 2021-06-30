#include "WMIC.h"

TableData* WMIQueryer::WMIGetData(std::vector<std::string> Fields, TableData* Data) {

    if (FAILED(this->WmiObj->hres))
    {
        LOG(WARNING) << "Failed to initialize security. Error code = 0x" << std::hex << this->WmiObj->hres;
        return NULL;
    }
    // 获取列名
    Data->Fields = Fields;
    Data->FieldsNum = Fields.size();

    std::for_each(Fields.begin(), Fields.end(), [&](std::string& field) {
        std::vector<std::string> values;
        while (this->WmiObj->pEnumerator)
        {
            // 逐一获得行数据
            HRESULT hr = this->WmiObj->pEnumerator->Next(WBEM_INFINITE, 1, &this->WmiObj->pclsObj, &this->WmiObj->uReturn);

            if (this->WmiObj->uReturn == 0)
            {
                
                break;
            }
            
            VARIANT vtProp;
            hr = this->WmiObj->pclsObj->Get(_bstr_t(field.c_str()), 0, &vtProp, 0, 0);
            if (SUCCEEDED(hr)) {
                // std::cout << _com_util::ConvertBSTRToString(vtProp.bstrVal) << std::endl;
                switch (vtProp.vt)
                {
                case VT_I4:
                    values.push_back(std::to_string(vtProp.intVal));
                    break;
                case VT_BSTR:
                    values.push_back(_com_util::ConvertBSTRToString(vtProp.bstrVal));
                    break;
                case VT_BOOL:
                    values.push_back(vtProp.boolVal?"TRUE":"FALSE");
                    break;
                case VT_EMPTY:
                    values.push_back("NULL");
                    break;
                default:
                    values.push_back("NULL");
                    break;
                }
                VariantClear(&vtProp);
            }
        }
        Data->Data.push_back(values);
        Data->RowsNum = values.size();
        LOG(INFO) << "Get Rows : " << Data->RowsNum << std::endl;
        this->WmiObj->pEnumerator->Reset();
    });
    return Data;
}

BOOL WMIQueryer::WMIShowTableData(TableData* Data) {
    if (Data->FieldsNum <= 0) {
        LOG(INFO) << "Fields count is NULL.";
        return FALSE;
    }
    for (auto& field : Data->Fields) {
        std::cout << field << "\t\t";
    }
    std::cout << std::endl;
    Data->RowsNum = Data->Data[0].size();
    for (size_t i = 0; i < Data->RowsNum; i++)
    {
        for (size_t c = 0; c < Data->FieldsNum; c++)
        {
            std::cout << Data->Data[c][i] << "\t\t";
        }
        std::cout << std::endl;
    }
    LOG(INFO) << "RowsNum : " << Data->RowsNum;
    return TRUE;
}

BOOL WMIQueryer::WMIShowData(std::vector<std::string> Fields) {
    if (FAILED(this->WmiObj->hres))
    {
        LOG(WARNING) << "Failed to initialize security. Error code = 0x" << std::hex << this->WmiObj->hres;
        return FALSE;
    }
    while (this->WmiObj->pEnumerator)
    {
        HRESULT hr = this->WmiObj->pEnumerator->Next(WBEM_INFINITE, 1, &this->WmiObj->pclsObj, &this->WmiObj->uReturn);

        if (0 == this->WmiObj->uReturn)
        {
            break;
        }

        std::for_each(Fields.begin(), Fields.end(), [&](std::string& field) {
            VARIANT vtProp;
            hr = this->WmiObj->pclsObj->Get(_bstr_t(field.c_str()), 0, &vtProp, 0, 0);
            if (SUCCEEDED(hr)) {
                std::cout << _com_util::ConvertBSTRToString(vtProp.bstrVal) << std::endl;
                // LOG(INFO) << "Query Execute Line ... ";
                VariantClear(&vtProp);
            }
        });
    }
    return TRUE;
}

BOOL WMIQueryer::WMIQuery(std::string QueryStr) {
    if (FAILED(this->WmiObj->hres))
    {
        LOG(WARNING) << "Failed to initialize security. Error code = 0x" << std::hex << this->WmiObj->hres;
        return FALSE;
    }
    this->WmiObj->pEnumerator = NULL;
    this->WmiObj->hres = this->WmiObj->pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t(QueryStr.c_str()),
        WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &this->WmiObj->pEnumerator);
    if (FAILED(this->WmiObj->hres))
    {
        LOG(WARNING) << "Query for operating system name failed. Error code = 0x" << std::hex << this->WmiObj->hres;
        return FALSE;               // Program has failed.
    }
    LOG(INFO) << "Query Execute Success. Query is : " << QueryStr;
    return TRUE;
}

BOOL WMIQueryer::OpenNamespace(std::string NameSpacePath) {
    if (FAILED(this->WmiObj->hres))
    {
        LOG(WARNING) << "wmi_open_namespace Failed to initialize security. Error code = 0x" << std::hex << this->WmiObj->hres;
        
        return FALSE;
    }

    this->WmiObj->hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&this->WmiObj->pLoc);

    if (FAILED(this->WmiObj->hres))
    {
        LOG(WARNING) << "Failed to create IWbemLocator object. Err code = 0x" << std::hex << this->WmiObj->hres;
        return FALSE;  // Program has failed.
    }

    this->WmiObj->hres = this->WmiObj->pLoc->ConnectServer(
        _bstr_t(NameSpacePath.c_str()), // Object path of WMI namespace
        NULL,                    // User name. NULL = current user
        NULL,                    // User password. NULL = current
        0,                       // Locale. NULL indicates current
        NULL,                    // Security flags.
        0,                       // Authority (for example, Kerberos)
        0,                       // Context object 
        &this->WmiObj->pSvc                    // pointer to IWbemServices proxy
    );
    if (FAILED(this->WmiObj->hres))
    {
        LOG(WARNING) << "Could not connect. Error code = 0x" << std::hex << this->WmiObj->hres;
        return FALSE;
    }
    LOG(INFO) << "Connected to " << NameSpacePath << " WMI namespace";
    this->WmiObj->hres = CoSetProxyBlanket(
        this->WmiObj->pSvc,                        // Indicates the proxy to set
        RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
        RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
        NULL,                        // Server principal name 
        RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
        RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
        NULL,                        // client identity
        EOAC_NONE                    // proxy capabilities 
    );

    if (FAILED(this->WmiObj->hres))
    {
        LOG(WARNING) << "Could not set proxy blanket. Error code = 0x" << std::hex << this->WmiObj->hres;
        return FALSE;  // Program has failed.
    }

    return TRUE;
}

WMIQueryer::WMIQueryer() {
    this->WmiObj = new WMI_STRUCT;
    this->WmiObj->hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(this->WmiObj->hres))
    {
        // Program has failed.
        LOG(WARNING) << "Failed to initialize COM library. Error code = 0x" << std::hex << this->WmiObj->hres;
        return;
    }
    this->WmiObj->hres = CoInitializeSecurity(
        NULL,
        -1,                          // COM authentication
        NULL,                        // Authentication services
        NULL,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
        NULL,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities 
        NULL                         // Reserved
    );

    if (FAILED(this->WmiObj->hres))
    {
        LOG(WARNING) << "wmi_connect_server Failed to initialize security. Error code = 0x" << std::hex << this->WmiObj->hres;
        return;
    }
}

WMIQueryer::~WMIQueryer() {
    if (this->WmiObj->pEnumerator)
        this->WmiObj->pEnumerator->Release();
    if (this->WmiObj->pclsObj)
        this->WmiObj->pclsObj->Release();
    if (this->WmiObj->pSvc)
        this->WmiObj->pSvc->Release();
    if (this->WmiObj->pLoc)
        this->WmiObj->pLoc->Release();
    CoUninitialize();
    if (this->WmiObj) {
        delete this->WmiObj;
    }
}