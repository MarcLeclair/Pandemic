#pragma once
#include "ODBC.h"
class SqlConnection
{
	
	
public:
	ODBC_Class Connection;
	void saveGame();
	SqlConnection();
	~SqlConnection();
	void sqlExecuteSelect(string *select, bool insert);
};

