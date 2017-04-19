#include "SqlConnection.h"


SqlConnection::SqlConnection(){}

void SqlConnection::saveGame() {

}

void SqlConnection::sqlExecuteSelect(string *select, bool insert) {

	SQLCHAR DBName[20] = "PandemicMain";
	SQLCHAR SQLStmt[4000] = { 0 };
	SQLCHAR SqlState[6],  Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLRETURN rc = SQL_SUCCESS;
	SQLSMALLINT   i, MsgLen;
	SQLRETURN rc2;
	ODBC_Class Example;
	SQLINTEGER    NativeError;
	if (Example.ConHandle != NULL)

	{
		Connection.colData.clear();
		rc = SQLConnect(Example.ConHandle, DBName, SQL_NTS, (SQLCHAR *) "concordia", SQL_NTS, (SQLCHAR *) "University4", SQL_NTS);

		// Allocate An SQL Statement Handle 

		rc = SQLAllocHandle(SQL_HANDLE_STMT, Example.ConHandle, &Example.StmtHandle);

		rc = SQLExecDirect(Example.StmtHandle, SQLStmt, SQL_NTS);


		if (rc == SQL_SUCCESS)

		{

			// Define A SELECT SQL Statement  
			char* finalSelect = new char[select->length() + 1];
			std::strcpy(finalSelect, select->c_str());

			//std::cout << finalSelect << std::endl;
			strcpy((char *)SQLStmt, finalSelect);

			// Prepare And Execute The SQL Statement  

			rc = SQLExecDirect(Example.StmtHandle, SQLStmt, SQL_NTS);

			if ((rc == SQL_SUCCESS_WITH_INFO) || (rc == SQL_ERROR)) {
				// Get the status records.  
				i = 1;
				while ((rc2 = SQLGetDiagRec(SQL_HANDLE_STMT, Example.StmtHandle, i, SqlState, &NativeError,
					Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) {
					cout << "SQLSTATE: " << SqlState << " NativeError: " << NativeError << " Msg: " << Msg << " MsgLen: " << MsgLen << endl;
					i++;
				}
			}

			// Display The Results Of The SQL Query  
			if (!rc == SQL_SUCCESS) {
				cout << "*************************** failed ***************" << endl;
			}
			if (rc == SQL_SUCCESS)

			{
				if (insert == false) {
					Example.GetResultset();
					Connection.colData = Example.colData;
				}



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
