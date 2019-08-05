#include "chatbot.h"

#include <iostream>

using namespace std;

char* Chatbot::getOption()
{
	cout << endl;
	cout << "Please select one of the options" << endl;
	cin >> option;

	cout << "\n*********************************************************************************" << endl;
	cout << endl;
	return option;
}

void Chatbot::Display(char* a)
{
	cout << a <<endl;
}

void Chatbot::Display(int a,char* b)
{
	cout << a << " "<< b <<endl;
}
