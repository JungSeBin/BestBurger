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
    TABLE_TASTE,
    TABLE_SELECTEDBURGER
};

typedef std::map<int, SQLWCHAR*> DBMapType;

class DBManager
{
public:
    DBManager();
    ~DBManager();

public:

    static DBManager& getInstance()
    {
        static DBManager instance;
        return instance;
    }

    void        Connect();
    SQLRETURN   DBConnect();
    void        DBDisConnect();
    bool        ErrorHandling(SQLRETURN ret, char* msg);
    SQLRETURN   Excute(SQLWCHAR* query);

    void        GetDataFromDB();
    SQLRETURN   GetDataFromTable(TableType tbType);
    void        InsertUserNameToDB(std::wstring name);
    void        SelectUserIDFromDB();
    int         GetUserID(){ return _UserID; }
    void        SelectBurgerByUserInfo();
    void        InsertUserPreference();
    void        test();

    const       DBMapType& GetTableMap(TableType tbType) const;
    const       std::wstring& GetName() { return _UserName; }

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
    DBMapType _SelectedBurgerMap;

    int    _UserID;
    std::wstring    _UserName;
};