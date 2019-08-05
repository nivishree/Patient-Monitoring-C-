#pragma once
#include "chatbot.h"

class Linker
{
public:
	Linker(IO& inputOutput);
	void process(char* questionid, char* optionid);

private:
	IO& m_inputOutput;
};
