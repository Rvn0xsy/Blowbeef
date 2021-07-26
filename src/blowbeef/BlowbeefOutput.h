#pragma once
#include <iostream>
#include <fstream>
#include <easylogging++.h>
#include "BlowbeefType.h"
#include "json/json.h"


class BlowbeefOutput
{
public:
	BlowbeefOutput(std::string outfile, BlowbeefOutputType Type);
	bool SetOutputType(BlowbeefOutputType Type);
	bool operator<<(TableData* Data);
	bool Write(TableData* Data);
	bool OpenFile(std::string OutFile);
	~BlowbeefOutput();
private:
	std::string outFileName;
	std::ofstream  outfile;
	BlowbeefOutputType FileType;
	Json::Value root;
	bool WriteHTML(TableData* Data);
	bool WriteJson(TableData* Data);
	bool WriteHead();
	bool WriteFoot();
};

