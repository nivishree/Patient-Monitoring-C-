

#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <Windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <cstringt.h>
#include <string>
#include <SQLExample/stdafx.h>
#include <SQLExample/Database.cpp>
#include <SQLExample/Chatbot.cpp>
#include <SQLExample/DataFetch.cpp>
#include <SQLExample/Linker.cpp>
#include <SQLExample/isNumber.cpp>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PatientMonitor
{
	TEST_CLASS(Datafetch)
	{
		Chatbot chatbot;
	public:
		
		TEST_METHOD(TestNumberOfOptionsForAquestion)
		{
			
			DataFetch obj(chatbot);
			int expected = 5;
			char questionid[]="1";
			int actual = obj.OptionCount(questionid);
			Assert::AreEqual(expected, actual);
			
		}
		TEST_METHOD(TestNumberOfOptionsForAQuestion_1)
		{
			DataFetch obj(chatbot);
			int expected = 5;
			char questionid[] = "12";
			int actual = obj.OptionCount(questionid);
			Assert::AreEqual(expected, actual);

		}
		TEST_METHOD(TestNumberOfOptionsForAQuestion_2)
		{
			int expected = 3;
			DataFetch obj(chatbot);
			Assert::AreEqual(expected, obj.MonitorIdFetch("5", "2"));

		}
		TEST_METHOD(TestNumberOfOptionsForAQuestion_3)
		{
			int expected = 10;
			DataFetch obj2(chatbot);
			Assert::AreEqual(expected, obj2.MonitorIdFetch("11", "3"));

		}
		TEST_METHOD(TestIfCorrectQuestionForGivenQuestionid_1)
		{
			DataFetch obj1(chatbot);
			int a;
			char* expected = "What kind of storage are you looking for ?";
			
			if (strcmp(expected, obj1.QuestionFetch("11")) == 0)
			{
				a = 1;
			}
			Assert::AreEqual(1, a);
		}
		TEST_METHOD(TestIFCorrectQuestionForGivenQuestionid_2)
		{
			DataFetch obj1(chatbot);
			int a;
			char* expected = "Do you require Microstream Co2 for capnography measurement ?";

			if (strcmp(expected, obj1.QuestionFetch("6")) == 0)
			{
				a = 1;
			}
			Assert::AreEqual(1, a);
		};
		TEST_METHOD(TestForMonitorNameGivenMonitorid_1)
		{


			DataFetch obj1(chatbot);
			int a;
			char* expected = "Avalon FM20";
			char monitorid[] = "2";
			if (strcmp(expected, obj1.MonitorNameFetch(monitorid)) == 0)
			{
				a = 1;
			}
			Assert::AreEqual(1, a);

		}
		TEST_METHOD(TestForMonitorNameGivenMonitorid_2)
		{


			DataFetch obj1(chatbot);
			int a;
			char* expected = "IntelliVue MP90";
			char monitorid[] = "21";
			if (strcmp(expected, obj1.MonitorNameFetch(monitorid)) == 0)
			{
				a = 1;
			}
			Assert::AreEqual(1, a);

		}
		TEST_METHOD(TestForMonitorNameGivenMonitorid_3)
		{
			
			DataFetch obj1(chatbot);
			int a;
			char* expected = "Efficia CM series";
			char monitorid[] = "28";
			if (strcmp(expected, obj1.MonitorNameFetch(monitorid)) == 0)
			{
				a = 1;
			}
			Assert::AreEqual(1, a);

		}
		TEST_METHOD(TestIfCorrectLinkedOuestionFetchedGivenOptionAndQuestionID_1)
		{
			DataFetch obj1(chatbot);
			int expected = 5;
			Assert::AreEqual(expected, obj1.LinkIdFetch("3", "2"));

		}

		TEST_METHOD(TestIfCorrectLinkedOuestionFetchedGivenOptionAndQuestionID_2)
		{
			DataFetch obj2(chatbot);
			int expected = 10;
			Assert::AreEqual(expected, obj2.LinkIdFetch("9", "2"));

		};
	};
}
