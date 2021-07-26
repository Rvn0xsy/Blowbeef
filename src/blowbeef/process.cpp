#include "process.h"

Process::Process(std::string tomlConfigFile)
{
    this->SetModuleName("Process");
    this->SetTomlConfigFile(tomlConfigFile);
    this->ParseTomlConfig();
}

VOID Process::HandleData() {
	if (std::count(this->moduleWMIKey.begin(), this->moduleWMIKey.end(), this->moduleWMIFilterKey) == 0)
	{
		LOG(ERROR) << "Not Found Filter Key";
		return;
	}
	int row = this->GetFilterKeyIndex();
	if (row < 0) {
		LOG(INFO) << "Not Found Filter Key";
	}
	// this->Queryer->WMIShowTableData(this->moduleQueryResultData);
	// std::cout << "ROW : " << row << std::endl;
	auto values = this->moduleQueryResultData->Data.at(row);
	for (auto & v : values)
	{
		for (auto &f : this->moduleWMIFilter)
		{
			if (v == f) {
				LOG(INFO) << "Found Process > " << f;
			}
		}
	}

}