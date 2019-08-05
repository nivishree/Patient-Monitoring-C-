#pragma once
#include "Database.h"
#include "chatbot.h"
class DataFetch : public Database
{
public:
	DataFetch(IO& inputOutput);
	char* QuestionFetch(char* linkid);
	void OptionFetch(char* questionid);
	int LinkIdFetch(char* questionid, char* optionid);
	int MonitorIdFetch(char* questionid, char* optionid);
	char* MonitorNameFetch(char* monitorid);
	int OptionCount(char* questionid);

private:
	IO& m_inputOutput;
};