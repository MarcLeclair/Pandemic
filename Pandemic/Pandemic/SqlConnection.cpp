#include "SqlConnection.h"


SqlConnection::SqlConnection(){}

void SqlConnection::saveGame() {

}

void SqlConnection::sqlExecuteSelect(string *select) {

	SQLCHAR DBName[20] = "PandemicMain";
	SQLCHAR SQLStmt[4000] = { 0 };
	SQLRETURN rc = SQL_SUCCESS;
	ODBC_Class Example;
	if (Example.ConHandle != NULL)

	{

		rc = SQLConnect(Example.ConHandle, DBName, SQL_NTS, (SQLCHAR *) "concordia", SQL_NTS, (SQLCHAR *) "University4", SQL_NTS);

		// Allocate An SQL Statement Handle 

		rc = SQLAllocHandle(SQL_HANDLE_STMT, Example.ConHandle, &Example.StmtHandle);

		rc = SQLExecDirect(Example.StmtHandle, SQLStmt, SQL_NTS);

		if (rc == SQL_SUCCESS)

		{

			// Define A SELECT SQL Statement  
			char* finalSelect = new char[select->length() + 1];
			std::strcpy(finalSelect, select->c_str());

			strcpy((char *)SQLStmt, finalSelect);

			// Prepare And Execute The SQL Statement  

				rc = SQLExecDirect(Example.StmtHandle, SQLStmt, SQL_NTS);

			// Display The Results Of The SQL Query  
			if (!rc == SQL_SUCCESS) {
				cout << "*************************** failed ***************" << endl;
			}
			if (rc == SQL_SUCCESS)

			{
				
				Example.GetResultset();
				Connection.colData = Example.colData;



				// At this point you would want to do something  

				// with the resultset, such as display it.  

			}

		}

		// Free The SQL Statement Handle  

		if (Example.StmtHandle != NULL)

			SQLFreeHandle(SQL_HANDLE_STMT, Example.StmtHandle);

		// Disconnect From The Northwind Sample Database  
		rc = SQLDisconnect(Example.ConHandle);

	}



}



SqlConnection::~SqlConnection()
{
}
