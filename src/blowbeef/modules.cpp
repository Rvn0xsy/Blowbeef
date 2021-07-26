#include "modules.h"

VOID Modules::Query()
{
	this->Queryer = new WMIQueryer;
	this->moduleQueryResultData = new TableData;
	this->moduleQueryResultData->Description = this->moduleWMIDescription;
	LOG(INFO) << "Handle :" << this->moduleQueryResultData->Description;
	Queryer->OpenNamespace(this->moduleWMINameSpace);
	Queryer->WMIQuery(this->moduleWMIQuery);
	this->moduleQueryResultData = Queryer->WMIGetData(this->moduleWMIKey, this->moduleQueryResultData);
	
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

VOID Modules::SetModuleName(std::string moduleName)
{
	this->moduleName = moduleName;
	return VOID();
}

VOID Modules::SetWMIDescription(std::string str)
{
	this->moduleWMIDescription = str;
	return VOID();
}

VOID Modules::SetWMIQuery(std::string str)
{
	this->moduleWMIQuery = str;
	return VOID();
}

VOID Modules::SetWMINameSpace(std::string str)
{
	this->moduleWMINameSpace = str;
	return VOID();
}
