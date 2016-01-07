#include "DBManager.h"
#include <stdio.h>
#include <tchar.h>
#include <vector>
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
    _ODBC_Name = (SQLWCHAR*)L"burgerDB";
    _ODBC_ID = (SQLWCHAR*)L"user";
    _ODBC_PW = (SQLWCHAR*)L"burger123";

    if (!ErrorHandling(DBConnect(), "DBConnect Error!!"))
    {
        DBDisConnect();
    }
    return;
}

void DBManager::Excute()
{
    if (!ErrorHandling(DBExcuteSQL(), "DBExcuteSQL Error!!"))
    {
        DBDisConnect();
    }
    return;
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

    unsigned int id;
    SQLWCHAR* name;
    SQLLEN iID, iName;

    ////���̺� �˻����� ���� �ڷῡ ���� ����

    //���̺� �˻�
    ret = SQLExecDirect(_HStmt, (SQLWCHAR*)L"SELECT id, name FROM burger", SQL_NTS);

    if (!ErrorHandling(ret, "SELECT Error!!"))
    {
        return ret;
    }

    //Select�� ������ ���
    wprintf(L"ID\t name\n");
    while (SQLFetch(_HStmt) != SQL_NO_DATA)
    {
        name = (SQLWCHAR*)malloc(sizeof(SQLWCHAR)* 50);
        SQLGetData(_HStmt, 1, SQL_C_ULONG, &id, 0, &iID);
        SQLGetData(_HStmt, 2, SQL_C_WCHAR, name, 50, &iName);

        _BurgerMap.insert(std::make_pair(id, name));
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
