#pragma once

////////////////////////////////////////
#include <windows.h>
#include <sql.h>
#include<sqltypes.h>
#include<sqlext.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;



// Define The ODBC_Class Class
class ODBC_Class
{
	struct ColDescription
	{
		SQLSMALLINT colNumber;
		SQLCHAR colName[80];
		SQLSMALLINT nameLen;
		SQLSMALLINT dataType;
		SQLULEN colSize;
		SQLSMALLINT decimalDigits;
		SQLSMALLINT nullable;
	};
	// Attributes
public:
	SQLHANDLE EnvHandle;
	SQLHANDLE ConHandle;
	SQLHANDLE StmtHandle;
	SQLRETURN rc;
	vector<ColDescription> cols;
	vector< vector<string> > colData;
	// Operations
public:
	ODBC_Class(); // Constructor
	~ODBC_Class(); // Destructor
	SQLRETURN GetResultset();
	void DescribeColumns();
private:
	_inline SQLRETURN Describe(ColDescription& c);
	SQLRETURN GetColData(int colnum, string& str);
};
