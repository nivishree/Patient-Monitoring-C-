#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <cstringt.h>
#include <string>

using namespace std;

class Database 
{

public:

	SQLHANDLE SQLEnvHandle = NULL;
	SQLHANDLE SQLConnectionHandle = NULL;
	SQLHANDLE SQLStatementHandle = NULL;
	SQLRETURN retCode = 0;


	void showSQLError(unsigned int handleType, const SQLHANDLE& handle);
	void connectdb();
	void disconnectdb();
	
	
};
void Database::showSQLError(unsigned int handleType, const SQLHANDLE& handle)
{
	SQLCHAR SQLState[1024];
	SQLCHAR message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
		cout << "SQL driver message :" << message << "\nSQL state :" << SQLState << ". " << endl;
}

void Database ::connectdb()

{
	do
	{
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			break;
		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			break;
		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=PatientMonitor; Trusted=True;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			cout << "Successfully Connected";
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

	} while (FALSE);
}

void Database::disconnectdb()
{
	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
}

class DataFetch : public Database
{

public:
	void QuestionFetch(char* linkid);
	void OptionFetch(char* questionid);
	int LinkIdFetch(char* questionid, char* optionid);
	int MonitorIdFetch(char* questionid,char* optionid);
	void MonitorNameFetch(char* monitorid);
	int OptionCount(char* questionid);
};

void DataFetch::QuestionFetch(char* linkid)
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

				cout << questions << endl;
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

	do{
		connectdb();
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS))
		{
			// Executes a preparable statement
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
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &optionid,sizeof(optionid), NULL);
				SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &options, sizeof(options), NULL);
				cout << optionid << " " <<options << endl;
			}
		}
	} while (FALSE);
}



// MONITOR DATA FETCHING FUNCTION

void DataFetch::MonitorNameFetch(char* monitorid)
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
				
				cout << "-----------------------------------------------------------------------" << endl;
				cout<<"The monitor which suites your requirement is - " << monitorname << endl;
			}
		}
	} while (FALSE);
}


// MONITOR ID FETCH FUNCTION

int DataFetch::MonitorIdFetch(char* questionid,char* optionid)
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

class chatbot
{
public:
	char option[5];

	char* getdata()
	{
		cout << "Please select one of the options" << endl;
		cin >> option;
		return option;
	}
};


class linker 
{
        public :
			void linkedquestion(char* questionid, char* optionid);
};

void linker:: linkedquestion(char* questionid, char* optionid)
{
	chatbot obj1;
	DataFetch obj2;
	int q, m;
	do {
		q = obj2.LinkIdFetch(questionid, optionid);
		if (q == 0)
		{
			m = obj2.MonitorIdFetch(questionid, optionid);
			char str[10];
			_itoa_s(m, str, 10);
			obj2.MonitorNameFetch(str);
		}
		else
		{
			char str1[10];
			_itoa_s(q, str1, 10);

			obj2.QuestionFetch(str1);
			obj2.OptionFetch(str1);
			questionid = str1;
			optionid = obj1.getdata();
			int o;
			o=atoi(optionid);
			int w=obj2.OptionCount(questionid);
			if (o > w)
			{
				cout << "Enter a valid option" << endl;
				optionid = obj1.getdata();
			}
		}
	} while (q != 0);
}

class IDataFetch                    //interface class
{
	   
public:
	virtual void QuestionFetch() = 0;
	virtual void OptionFetch(char* questionid) = 0;
	virtual int LinkIdFetch(char* questionid, char* optionid) = 0;
	virtual int MonitorIdFetch(char* questionid, char* optionid) = 0;
	virtual void MonitorNameFetch(char* monitorid) = 0;
};

class IDatabase
{
public:

    virtual void showSQLError(unsigned int handleType, const SQLHANDLE& handle) = 0;
    virtual void connectdb() = 0;
	virtual void disconnectdb() = 0;
};


int main()
{
	
	chatbot obj1;
	DataFetch obj2;
	linker obj3;
	const unsigned BUFFER_SIZE = 200;
	
	char firstoption[BUFFER_SIZE];
	char question[128] ="1";


	
	obj2.QuestionFetch(question);
	obj2.OptionFetch(question);
	strncpy_s(firstoption, obj1.getdata(),BUFFER_SIZE - strlen(firstoption) - 1);
	//cout << firstoption;
	//cin >> firstoption;
	
	obj3.linkedquestion(question, firstoption);
	getchar();
	return 0;
}