#include "modules.h"

BOOL Modules::ParseTomlConfig()
{	
	if (this->tomlConfigFile.empty())
	{
		LOG(ERROR) << "NOT Found Toml Config File.";
		return FALSE;
	}
	try {
		auto config = toml::parse(this->tomlConfigFile);
		this->module = toml::find(config, this->moduleName);
		this->moduleWMIKey = toml::find<std::vector<std::string>>(this->module, "wmi_query_key");
		this->moduleWMIFilter = toml::find<std::vector<std::string>>(this->module, "filter");
		this->moduleWMINameSpace = toml::find_or<std::string>(this->module, "wmi_namespace","root\\cimv2");
		this->moduleWMIQuery = toml::find<std::string>(this->module, "wmi_query");
		this->moduleWMIDescription = toml::find<std::string>(this->module, "description");
		this->moduleWMIFilterKey = toml::find_or<std::string>(this->module, "filter_key","");
	}
	catch (std::exception e) {
		LOG(ERROR) << e.what();
		return FALSE;
	}
	return TRUE;
}

VOID Modules::SetTomlConfigFile(std::string tomlConfigFile)
{
	this->tomlConfigFile = tomlConfigFile;
	return VOID();
}

VOID Modules::Query()
{
	this->Queryer = new WMIQueryer;
	this->moduleQueryResultData = new TableData;
	this->moduleQueryResultData->Description = this->moduleWMIDescription;
	LOG(INFO) << "Handle :" << this->moduleQueryResultData->Description;
	Queryer->OpenNamespace(this->moduleWMINameSpace);
	Queryer->WMIQuery(this->moduleWMIQuery);
	this->moduleQueryResultData = Queryer->WMIGetData(this->moduleWMIKey, this->moduleQueryResultData);
	// LOG(INFO) << "Get Rows Data :" << this->moduleQueryResultData->Data.size();
	return VOID();
}

VOID Modules::HandleData()
{
	this->Queryer->WMIShowTableData(this->moduleQueryResultData);
	return VOID();
}


VOID Modules::Release()
{
	if (this->moduleQueryResultData) {
		delete this->moduleQueryResultData;
	}
	this->Queryer->Release();
	return VOID();
}

TableData* Modules::GetData()
{
	return this->moduleQueryResultData;
}

int Modules::GetFilterKeyIndex()
{
	for (auto& field : this->moduleWMIKey)
	{
		auto iter = std::find(this->moduleWMIKey.begin(), this->moduleWMIKey.end(), this->moduleWMIFilterKey);
		if (iter == this->moduleWMIKey.end()) {
			continue;
		}
		return std::distance(this->moduleWMIKey.begin(), iter);
	}
	return -1;
}

VOID Modules::SetModuleName(std::string moduleName)
{
	this->moduleName = moduleName;
	return VOID();
}
