#include "BlowbeefOutput.h"

BlowbeefOutput::BlowbeefOutput(std::string OutFile, BlowbeefOutputType Type)
{
	this->OpenFile(OutFile);
	this->SetOutputType(Type);
	this->WriteHead();
}


bool BlowbeefOutput::SetOutputType(BlowbeefOutputType Type)
{
	this->FileType = Type;
	return true;
}

bool BlowbeefOutput::operator<<(TableData* Data)
{
	if (!this->outfile.is_open()) {
		LOG(ERROR) << "File is Not Open.";
		return false;
	}
	this->Write(Data);
	return true;
}

bool BlowbeefOutput::Write(TableData* Data)
{
	switch (this->FileType)
	{
	case BlowbeefOutputType::CSV:
		LOG(INFO) << "Write CSV Format Result.";
		break;
	case BlowbeefOutputType::LOG:
		LOG(INFO) << "Write LOG Format Result.";
		break;
	case BlowbeefOutputType::HTML:
		LOG(INFO) << "Write HTML Format Result.";
		this->WriteHTML(Data);
		break;
	default:
		break;
	}
	return false;
}

bool BlowbeefOutput::OpenFile(std::string OutFile)
{
	this->outfile.open(OutFile, std::ios::app);
	return true;
}

BlowbeefOutput::~BlowbeefOutput()
{
	
	this->WriteFoot();
	this->outfile.close();
}

bool BlowbeefOutput::WriteHTML(TableData * Data)
{
	if (!this->outfile.is_open()) {
		LOG(ERROR) << "File is Not Open.";
		return false;
	}
	if (Data->FieldsNum <= 0) {
		LOG(INFO) << "Fields count is NULL.";
		return FALSE;
	}
	this->outfile << "<hr>";
	this->outfile << "<h1>" << Data->Description << "</h1>";
	this->outfile << "<table border=\"1\">";
	this->outfile << "<tr>";
	for (auto& field : Data->Fields) {
		this->outfile << "<th>" <<field << "</th>";
	}
	Data->RowsNum = Data->Data[0].size();
	for (int i = 0; i < Data->RowsNum; i++)
	{
		this->outfile << "<tr>";
		for (int c = 0; c < Data->FieldsNum; c++)
		{
			this->outfile<< "<td>" << Data->Data[c][i] << "</td>";
		}
		this->outfile << "</tr>";
	}
	
	return true;
}

bool BlowbeefOutput::WriteHead()
{
	switch (this->FileType)
	{
	case BlowbeefOutputType::CSV:
		LOG(INFO) << "Write CSV Format Result.";
		break;
	case BlowbeefOutputType::LOG:
		LOG(INFO) << "Write LOG Format Result.";
		break;
	case BlowbeefOutputType::HTML:
		LOG(INFO) << "Write HTML Format Result.";
		this->outfile << "<html><body>";
		break;
	default:
		break;
	}
	return true;
}

bool BlowbeefOutput::WriteFoot()
{
	if (!this->OpenFile(this->outFileName)) {
		abort();
	}
	switch (this->FileType)
	{
	case BlowbeefOutputType::CSV:
		LOG(INFO) << "Write CSV Format Result.";
		break;
	case BlowbeefOutputType::LOG:
		LOG(INFO) << "Write LOG Format Result.";
		break;
	case BlowbeefOutputType::HTML:
		LOG(INFO) << "Write HTML Format Result.";
		this->outfile << "</table></body></html>";
		break;
	default:
		break;
	}
	return true;
}

