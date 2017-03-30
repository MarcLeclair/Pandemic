#include "ODBC.h"

//***************************CODE FROM http://www.dreamincode.net/forums/topic/127959-odbc-c-example/ *************************************/
// Define The ODBC_Class Class


// Define The Class Constructor
ODBC_Class::ODBC_Class()
{
	// Initialize The Return Code Variable
	rc = SQL_SUCCESS;
	// Allocate An Environment Handle
	rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &EnvHandle);
	// Set The ODBC Application Version To 3.x
	if (rc == SQL_SUCCESS)
		rc = SQLSetEnvAttr(EnvHandle, SQL_ATTR_ODBC_VERSION,
		(SQLPOINTER)SQL_OV_ODBC3, SQL_IS_UINTEGER);
	// Allocate A Connection Handle
	if (rc == SQL_SUCCESS)
		rc = SQLAllocHandle(SQL_HANDLE_DBC, EnvHandle, &ConHandle);
}

// Define The Class Destructor
ODBC_Class::~ODBC_Class()
{
	// Free The Connection Handle
	if (ConHandle != NULL)
		SQLFreeHandle(SQL_HANDLE_DBC, ConHandle);
	// Free The Environment Handle
	if (EnvHandle != NULL)
		SQLFreeHandle(SQL_HANDLE_ENV, EnvHandle);
}

// Get the data for one column and return the info in the form
// of a std::string.  The ODBC driver will make all necessary
// data conversions from whatever type the data is in the database
// to SQL_CHAR.  You could make this function more comples by 
// getting the return type as it appears in the database then constructing
// a VARIANT object to hold the data.
SQLRETURN ODBC_Class::GetColData(int colnum, string& str)
{
	SQLCHAR buf[255] = { 0 };
	if ((rc = SQLGetData(StmtHandle, colnum, SQL_CHAR, buf, sizeof(buf), NULL)) == SQL_SUCCESS)
		str = reinterpret_cast<char*>(buf);
	return rc;
}

//
// Define The ShowResults() Member Function
SQLRETURN ODBC_Class::GetResultset()
{
	// Get all column description
	DescribeColumns();
	// erase anything that's in the colData vector
	colData.clear();
	// fetch a row from the resultset
	while (SQLFetch(StmtHandle) == SQL_SUCCESS)
	{
		// vector of strings to hold the column data
		vector<string> col;
		string data;
		// column counter
		int i = 1;
		// get the data for each column and add it to 
		// the col vector
		while (GetColData(i, data) == SQL_SUCCESS)
		{
			col.push_back(data);
			++i; // increment the column number
		}
		// add column data to the colData vector
		colData.push_back(col);
	}
	return SQL_SUCCESS;
}

// Get the description for one column in the resultset.
// This was made a seprate function to simplify the coding
SQLRETURN  ODBC_Class::Describe(ColDescription& c)
{
	return SQLDescribeCol(StmtHandle, c.colNumber,
		c.colName, sizeof(c.colName), &c.nameLen,
		&c.dataType, &c.colSize, &c.decimalDigits, &c.nullable);
}

// Get the description for all the columns in the resultset.
void ODBC_Class::DescribeColumns()
{
	ColDescription c;
	c.colNumber = 1;
	cols.clear();
	while (Describe(c) == SQL_SUCCESS)
	{
		cols.push_back(c);
		++c.colNumber;
	}

}