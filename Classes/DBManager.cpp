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

// ODBC사용 핸들 할당 및 SQL연결
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

// 연결 해제 및 핸들 반환
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
    char name[50];
    SQLLEN iID, iName;

    ////테이블 검색으로 받을 자료에 대한 선언

    //테이블 검색
    ret = SQLExecDirect(_HStmt, (SQLWCHAR*)L"SELECT id, name FROM burger", SQL_NTS);

    if (!ErrorHandling(ret, "SELECT Error!!"))
    {
        return ret;
    }

    //Select한 데이터 출력
    wprintf(L"ID\t name\n");
    while (SQLFetch(_HStmt) != SQL_NO_DATA)
    {
        SQLGetData(_HStmt, 1, SQL_C_ULONG, &id, 0, &iID);
        SQLGetData(_HStmt, 2, SQL_C_WCHAR, name, 50, &iName);
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
