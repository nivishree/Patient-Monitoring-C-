#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <cstringt.h>
#include <string>
#include "chatbot.h"
#include "Database.h"
#include "DataFetch.h"
#include "Linker.h"
#include "isNumber.h"

using namespace std;

int main()
{

	Chatbot chatbot1;
	DataFetch datafetch1(chatbot1);
	Linker linker1(chatbot1);

	const unsigned BUFFER_SIZE = 200;

	char firstoption[BUFFER_SIZE];
	char question[] = "1";
	cout << "Hi User, Welcome . I am Elbot!" << endl;
	cout << "Let's chat,press a key to continue. " << endl;
	getchar();
	datafetch1.QuestionFetch(question);
	datafetch1.OptionFetch(question);
	strncpy_s(firstoption, chatbot1.getOption(), BUFFER_SIZE - strlen(firstoption) - 1);
	int o;
	o = atoi(firstoption);
	int w = datafetch1.OptionCount(question);
	while (o > w || isNumber(firstoption) == 0)
	{
		cout << "Enter a valid option" << endl;
		strncpy_s(firstoption, chatbot1.getOption(), BUFFER_SIZE - strlen(firstoption) - 1);
		o = atoi(firstoption);
	}
	linker1.process(question, firstoption);

	return 0;
}