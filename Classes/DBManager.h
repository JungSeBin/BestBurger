#pragma once

#include <windows.h>
#include "sql.h"
#include "sqlext.h"

class DBManager
{
public:
    DBManager();
    ~DBManager();

public:
    void Connect();
    SQLRETURN DBConnect();
    void Excute();
    SQLRETURN DBExcuteSQL();
    void DBDisConnect();
    bool ErrorHandling(SQLRETURN ret, char* msg);

    static DBManager& getInstance()
    {
        static DBManager instance;
        return instance;
    }

private:

    SQLHENV _HEnv;
    SQLHDBC _HDbc;
    SQLHSTMT _HStmt;

    SQLWCHAR* _ODBC_Name = (SQLWCHAR*)L"burgerDB";
    SQLWCHAR* _ODBC_ID = (SQLWCHAR*)L"user";
    SQLWCHAR* _ODBC_PW = (SQLWCHAR*)L"burger123";
};