#include "DBManager.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)

DBManager::DBManager()
{
    Connect();
}


DBManager::~DBManager()
{
    DBDisConnect();
}

void DBManager::Connect()
{
    if (!ErrorHandling(DBConnect(), "DBConnect Error!!"))
    {
        std::cout << "DBConnect Error" << std::endl;
        DBDisConnect();
        return ;
    }
}

void DBManager::Excute()
{
    if (!ErrorHandling(DBExcuteSQL(), "DBExcuteSQL Error!!"))
    {
        std::cout << "DBExcuteQuery Error" << std::endl;
        DBDisConnect();
        return ;
    }
}

// ODBC��� �ڵ� �Ҵ� �� SQL����
SQLRETURN DBManager::DBConnect()
{
    SQLRETURN ret = SQL_SUCCESS;

    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_HEnv);
    if (!ErrorHandling(ret, "SQLAllocHandle Error!"))
    {
        return ret;
    }

    ret = SQLSetEnvAttr(_HEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
    if (!ErrorHandling(ret, "SQLSetEnvAttrError!"))
    {
        return ret;
    }

    ret = SQLAllocHandle(SQL_HANDLE_DBC, _HEnv, &_HDbc);
    if (!ErrorHandling(ret, "SQLAllocHandle Error!"))
    {
        return ret;
    }

    ret = SQLConnect(_HDbc, _ODBC_Name, SQL_NTS, _ODBC_ID, SQL_NTS, _ODBC_PW, SQL_NTS);
    if (!ErrorHandling(ret, "SQLConnect Error!"))
    {
        return ret;
    }

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _HDbc, &_HStmt);
    if (!ErrorHandling(ret, "SQLAllocHandle Error!"))
    {
        return ret;
    }

    return ret;
}

// ���� ���� �� �ڵ� ��ȯ
void DBManager::DBDisConnect()
{
    if (_HStmt) SQLFreeHandle(SQL_HANDLE_STMT, _HStmt);
    if (_HDbc) SQLDisconnect(_HDbc);
    if (_HDbc) SQLFreeHandle(SQL_HANDLE_DBC, _HDbc);
    if (_HEnv) SQLFreeHandle(SQL_HANDLE_ENV, _HEnv);
}

SQLRETURN DBManager::DBExcuteSQL()
{
    SQLRETURN ret = SQL_SUCCESS;

    int id;
    char name[50], trackName[100];
    SQLLEN iID, iName, iTrackName;

    ////���̺� �˻����� ���� �ڷῡ ���� ����

    //���̺� �˻�
    ret = SQLExecDirect(_HStmt, (SQLWCHAR*)L"SELECT id, title FROM book_inventory", SQL_NTS);

    if (!ErrorHandling(ret, "SELECT Error!!"))
    {
        return ret;
    }

    //Select�� ������ ���
    wprintf(L"Track\t ID\t Name\n");
    while (SQLFetch(_HStmt) != SQL_NO_DATA)
    {
        SQLGetData(_HStmt, 1, SQL_C_ULONG, &id, 0, &iID);
        SQLGetData(_HStmt, 2, SQL_C_WCHAR, trackName, 50, &iTrackName);
    }

    if (_HStmt) SQLCloseCursor(_HStmt);

    return ret;
}

bool DBManager::ErrorHandling(SQLRETURN ret, char* msg)
{
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
    {
        return true;
    }
    else
    {
        char error[255] = { 0, };
        sprintf_s(error, "%s error No: %d\n", msg, GetLastError());
        fputs(error, stderr);
        return false;
    }
}
