#include "DataFetch.h"
#include <iostream>
#include <Windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include "Database.h"
#include "chatbot.h"


using namespace std;
DataFetch::DataFetch(IO& inputOutput) :m_inputOutput(inputOutput)
{



}





char* DataFetch::QuestionFetch(char* linkid)
{

	// Query statement
	const unsigned BUFFER_SIZE = 200;
	char SQLQuery[BUFFER_SIZE];
	strncpy_s(SQLQuery, "SELECT questions FROM question_table where questionid=", BUFFER_SIZE - 1); //-1 for null-termination
	strncat_s(SQLQuery, linkid, BUFFER_SIZE - strlen(SQLQuery) - 1); //-1 for null-termination
	
	//Connecting to DB and querying
	do
	{
		connectdb();
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS))
		{
			// Executes a preparable statement
			cout << "Invalid input" << endl;
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else
		{


			//Querying functions
			char questions[200];
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
			{
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &questions, sizeof(questions), NULL);


				m_inputOutput.Display(questions);
				return questions;
			}
		}
	} while (FALSE);
}
int DataFetch::OptionCount(char* question_id)
{
	const unsigned BUFFER_SIZE = 200;
	char SQLQuery[BUFFER_SIZE];
	strncpy_s(SQLQuery, "SELECT count(optionid) FROM optiontable where question_id=", BUFFER_SIZE - 1); //-1 for null-termination
	strncat_s(SQLQuery, question_id, BUFFER_SIZE - strlen(SQLQuery) - 1); //-1 for null-termination

	do {
		connectdb();
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS))
		{
			// Executes a preparable statement
			cout << " Invalid input" << endl;
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else
		{

			//Querying functions
			char options[200];
			int optionid;
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
			{
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &(optionid), sizeof(optionid), NULL);

				return optionid;
			}
		}
	} while (FALSE);

}

void DataFetch::OptionFetch(char* question_id)
{

	// Query statement
	const unsigned BUFFER_SIZE = 200;
	char SQLQuery[BUFFER_SIZE];
	strncpy_s(SQLQuery, "SELECT optionid,options FROM optiontable where question_id=", BUFFER_SIZE - 1); //-1 for null-termination
	strncat_s(SQLQuery, question_id, BUFFER_SIZE - strlen(SQLQuery) - 1); //-1 for null-termination

	
	//Connecting to DB and querying
	do
	{
		connectdb();
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS))
		{
			// Executes a preparable statement
			cout << "Invalid input" << endl;
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else
		{

			//Querying functions
			char options[200];
			int optionid;
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
			{
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &optionid, sizeof(optionid), NULL);
				SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &options, sizeof(options), NULL);


				m_inputOutput.Display(optionid, options);

			}
		}
	} while (FALSE);
}



// MONITOR DATA FETCHING FUNCTION

char* DataFetch::MonitorNameFetch(char* monitorid)
{

	// Query statement
	const unsigned BUFFER_SIZE = 200;
	char SQLQuery[BUFFER_SIZE];
	strncpy_s(SQLQuery, "SELECT monitorname FROM monitors where monitorid=", BUFFER_SIZE - 1); //-1 for null-termination
	strncat_s(SQLQuery, monitorid, BUFFER_SIZE - strlen(SQLQuery) - 1); //-1 for null-termination


	//Connecting to DB and querying
	do
	{
		connectdb();
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS))
		{
			// Executes a preparable statement
			cout << "Invalid input" << endl;
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else
		{

			//Querying functions
			char monitorname[200];
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
			{
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &monitorname, sizeof(monitorname), NULL);

				cout << "-----------------------------------------------------------------------------------" << endl;
				cout << "The monitor which suites your requirement is - " << endl;

				Chatbot disp;
				disp.Display(monitorname);

				cout << "-----------------------------------------------------------------------------------" << endl;
				cout << "\n\n\nThanks for reaching out to me! Hope I helped you to select an apt patient monitor.\nNeed more information or have any queries? \nThen please visit our website https://www.philips.co.in/healthcare/solutions/patient-monitoring/patient-monitoring or \ncontact our 24*7 customer support via an email - call.ccc@philips.com or call  1-800-419-6788.\nBye!Have a good day !!:D\n\n\n\n" << endl;

				return monitorname;
			}
		}
	} while (FALSE);
}


// MONITOR ID FETCH FUNCTION

int DataFetch::MonitorIdFetch(char* questionid, char* optionid)
{
	// Query statement
	const unsigned BUFFER_SIZE = 200;
	char SQLQuery[BUFFER_SIZE];
	strncpy_s(SQLQuery, "SELECT monitor_id FROM optiontable where question_id=", BUFFER_SIZE - 1); //-1 for null-termination
	strncat_s(SQLQuery, questionid, BUFFER_SIZE - strlen(SQLQuery) - 1); //-1 for null-termination
	char opt[] = "AND optionid=";
	strncat_s(SQLQuery, opt, BUFFER_SIZE - strlen(SQLQuery) - 1);
	strncat_s(SQLQuery, optionid, BUFFER_SIZE - strlen(SQLQuery) - 1);

	//Connecting to DB and querying
	do
	{
		connectdb();
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS))
		{
			// Executes a preparable statement
			cout << "Invalid input" << endl;
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else
		{

			//Querying functions
			int monitorid;
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
			{
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &monitorid, sizeof(monitorid), NULL);

				//cout << monitorid << endl;

				return monitorid;
			}
		}
	} while (FALSE);
}


int DataFetch::LinkIdFetch(char* questionid, char* optionid)
{
	// Query statement
	const unsigned BUFFER_SIZE = 200;
	char SQLQuery[BUFFER_SIZE];
	strncpy_s(SQLQuery, "SELECT linkid FROM optiontable where question_id=", BUFFER_SIZE - 1); //-1 for null-termination
	strncat_s(SQLQuery, questionid, BUFFER_SIZE - strlen(SQLQuery) - 1); //-1 for null-termination
	char opt[] = "AND optionid=";
	strncat_s(SQLQuery, opt, BUFFER_SIZE - strlen(SQLQuery) - 1);
	strncat_s(SQLQuery, optionid, BUFFER_SIZE - strlen(SQLQuery) - 1);

	//Connecting to DB and querying
	do
	{
		connectdb();
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS))
		{
			// Executes a preparable statement
			cout << "Invalid input" << endl;
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else
		{

			//Querying functions
			int linkid;
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
			{
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &linkid, sizeof(linkid), NULL);

				//cout << monitorid << endl;

				return linkid;
			}
		}
	} while (FALSE);
}

