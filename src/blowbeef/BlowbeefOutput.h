#pragma once
#include <iostream>
#include <fstream>
#include <easylogging++.h>
#include "BlowbeefType.h"



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
	bool WriteHTML(TableData* Data);
	bool WriteHead();
	bool WriteFoot();
};

