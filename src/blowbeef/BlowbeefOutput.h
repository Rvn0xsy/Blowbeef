#pragma once
#include <iostream>

enum class BlowbeefOutputType
{
	CSV,
	HTML,
	LOG
};

class BlowbeefOutput
{
public:
	BlowbeefOutput(std::string OutFile);
	bool SetOutputType(BlowbeefOutputType Type);

private:
	std::string OutFile;
};

