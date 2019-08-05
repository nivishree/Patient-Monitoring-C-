#pragma once
#include<string>
using namespace std;
class IO
{
public:
	virtual void Display(char*) = 0;
	virtual void Display(int, char*) = 0;
	virtual char* getOption()=0 ;
};

class Chatbot: public IO
{
public :
	char option[5];
	void Display(char*);
	void Display(int,char*);
	char* getOption();
	
};