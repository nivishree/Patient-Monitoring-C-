#pragma once

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

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
