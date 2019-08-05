#include "Linker.h"
#include "Chatbot.h"
#include "DataFetch.h"
#include <iostream>
#include "isNumber.h"

 

using namespace std;

 


Linker::Linker(IO& inputOutput):m_inputOutput(inputOutput)
{

 

}

 

void Linker::process(char* questionid, char* optionid)
{
    //Chatbot obj1;
    DataFetch datafetch1(m_inputOutput);
    int q, m;
	q = datafetch1.LinkIdFetch(questionid, optionid);
    while(q!=0)
	{
        q = datafetch1.LinkIdFetch(questionid, optionid);
        if (q == 0)
        {
            m = datafetch1.MonitorIdFetch(questionid, optionid);
            char str[10];
            _itoa_s(m, str, 10);
            datafetch1.MonitorNameFetch(str);
        }
        else
        {
            char str1[10];
            _itoa_s(q, str1, 10);

            datafetch1.QuestionFetch(str1);
            datafetch1.OptionFetch(str1);
            questionid = str1;
            optionid = m_inputOutput.getOption();
            int o;
            o = atoi(optionid);
            int w = datafetch1.OptionCount(questionid);
            while (o > w || isNumber(optionid)==0)
            {
                cout << "Enter a valid option" << endl;
                optionid = m_inputOutput.getOption();
                o = atoi(optionid);
            }
        }
    } 
}