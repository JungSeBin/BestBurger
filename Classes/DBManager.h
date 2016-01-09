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

typedef std::map<int, SQLWCHAR*> DBMapType;

class DBManager
{
public:
    DBManager();
    ~DBManager();

public:
    void Connect();
    SQLRETURN DBConnect();
    void Excute();
    void GetDataFromDB();
    SQLRETURN GetDataFromTable(TableType tbType);
    void DBDisConnect();
    bool ErrorHandling(SQLRETURN ret, char* msg);

    const DBMapType& GetTableMap(TableType tbType) const;

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

    DBMapType _BurgerMap;
    DBMapType _IngredientMap;
    DBMapType _SauceMap;
    DBMapType _TasteMap;
};