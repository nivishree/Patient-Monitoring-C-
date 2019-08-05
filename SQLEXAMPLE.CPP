// SQLExample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <cstringt.h>

using namespace std;


void showSQLError(unsigned int handleType, const SQLHANDLE& handle)
{
	SQLCHAR SQLState[1024];
	SQLCHAR message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
		cout << "SQL driver message :" << message << "\nSQL state :" << SQLState << ". " << endl;
}


int main()
{

	SQLHANDLE SQLEnvHandle = NULL;
	SQLHANDLE SQLConnectionHandle = NULL;
	SQLHANDLE SQLStatementHandle = NULL;
	SQLRETURN retCode = 0;
	char i[]="5";
	char SQLQuery[] = "SELECT optionid FROM optiontable where question_id=2 ";
	

		//const unsigned BUFFER_SIZE = 200;
		//char SQLQuery[BUFFER_SIZE];
		//strncpy_s(SQLQuery, "SELECT monitor_id FROM optiontable where question_id=", BUFFER_SIZE - 1); //-1 for null-termination
		//char a[] = "5";
		//strncat_s(SQLQuery, a, BUFFER_SIZE - strlen(SQLQuery) - 1); //-1 for null-termination
		//std::cout << SQLQuery << std::endl;
		
	

	
	


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

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else {
			char questions[856],options[800],optionid[10];
			int age,monitor_id,linkid;


			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
				// Fetches the next rowset of data from the result
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &optionid, sizeof(optionid), NULL);
				//(SQLStatementHandle, 1, SQL_C_DEFAULT, &options, sizeof(options), NULL);
				//SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &linkid, sizeof(linkid), NULL);
				//SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &monitor_id, sizeof(monitor_id), NULL);
				// Retrieves data for a single column in the result set
				cout  << optionid <<endl;
				//cout << optionid <<" "<<options << " "<<linkid <<" "<<monitor_id << endl;
			}
		}
	} while (FALSE);

	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	// Frees the resources and disconnects


}




