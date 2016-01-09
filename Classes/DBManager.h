#pragma once

#include <windows.h>
#include <iostream>
#include <map>

#include "sql.h"
#include "sqlext.h"

enum TableType
{
    TABLE_NONE,
    TABLE_BURGER,
    TABLE_INGREDIENT,
    TABLE_SAUCE,
    TABLE_TASTE
};

class DBManager
{
public:
    DBManager();
    ~DBManager();

public:
    void Connect();
    SQLRETURN DBConnect();
    void Excute();
    SQLRETURN GetDataFromDB(TableType tbType);
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

    SQLWCHAR* _ODBC_Name;
    SQLWCHAR* _ODBC_ID;
    SQLWCHAR* _ODBC_PW;

    std::map<int, SQLWCHAR*> _BurgerMap;
    std::map<int, SQLWCHAR*> _IngredientMap;
    std::map<int, SQLWCHAR*> _SauceMap;
    std::map<int, SQLWCHAR*> _TasteMap;
};