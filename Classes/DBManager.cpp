#include "DBManager.h"
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>

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
}

SQLRETURN DBManager::Excute(SQLWCHAR* query)
{
    SQLRETURN ret = SQL_SUCCESS;

    ret = SQLExecDirect(_HStmt, query, SQL_NTS);
    if (!ErrorHandling(ret, "Excute Query"))
    {
        return ret;
    }

    if (_HStmt) SQLCloseCursor(_HStmt);

    return ret;
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

    _BurgerMap.clear();
}

SQLRETURN DBManager::GetDataFromTable(TableType tbType)
{
    SQLRETURN ret = SQL_SUCCESS;

    unsigned int id;
    SQLWCHAR* name;
    SQLLEN iID, iName;

    switch (tbType)
    {
    case TABLE_NONE:
        break;
    case TABLE_BURGER:
        ret = SQLExecDirect(_HStmt, (SQLWCHAR*)L"SELECT id, name FROM burger", SQL_NTS);

        if (!ErrorHandling(ret, "SELECT Error!!"))
        {
            return ret;
        }

        while (SQLFetch(_HStmt) != SQL_NO_DATA)
        {
            name = (SQLWCHAR*)malloc(sizeof(SQLWCHAR)* 60);
            SQLGetData(_HStmt, 1, SQL_C_ULONG, &id, 0, &iID);
            SQLGetData(_HStmt, 2, SQL_C_WCHAR, name, 60, &iName);

            _BurgerMap.insert(std::make_pair(id, name));
        }
        break;
    case TABLE_INGREDIENT:
        ret = SQLExecDirect(_HStmt, (SQLWCHAR*)L"SELECT id, name FROM ingredient", SQL_NTS);

        if (!ErrorHandling(ret, "SELECT Error!!"))
        {
            return ret;
        }

        while (SQLFetch(_HStmt) != SQL_NO_DATA)
        {
            name = (SQLWCHAR*)malloc(sizeof(SQLWCHAR)* 50);
            SQLGetData(_HStmt, 1, SQL_C_ULONG, &id, 0, &iID);
            SQLGetData(_HStmt, 2, SQL_C_WCHAR, name, 50, &iName);

            _IngredientMap.insert(std::make_pair(id, name));
        }
        break;
    case TABLE_SAUCE:
        ret = SQLExecDirect(_HStmt, (SQLWCHAR*)L"SELECT id, name FROM sauce", SQL_NTS);

        if (!ErrorHandling(ret, "SELECT Error!!"))
        {
            return ret;
        }

        while (SQLFetch(_HStmt) != SQL_NO_DATA)
        {
            name = (SQLWCHAR*)malloc(sizeof(SQLWCHAR)* 50);
            SQLGetData(_HStmt, 1, SQL_C_ULONG, &id, 0, &iID);
            SQLGetData(_HStmt, 2, SQL_C_WCHAR, name, 50, &iName);

            _SauceMap.insert(std::make_pair(id, name));
        }
        break;
    case TABLE_TASTE:
        ret = SQLExecDirect(_HStmt, (SQLWCHAR*)L"SELECT id, name FROM taste", SQL_NTS);

        if (!ErrorHandling(ret, "SELECT Error!!"))
        {
            return ret;
        }

        while (SQLFetch(_HStmt) != SQL_NO_DATA)
        {
            name = (SQLWCHAR*)malloc(sizeof(SQLWCHAR)* 50);
            SQLGetData(_HStmt, 1, SQL_C_ULONG, &id, 0, &iID);
            SQLGetData(_HStmt, 2, SQL_C_WCHAR, name, 50, &iName);

            _TasteMap.insert(std::make_pair(id, name));
        }
        break;
    default:
        break;
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

void DBManager::GetDataFromDB()
{
    GetDataFromTable(TABLE_BURGER);
    GetDataFromTable(TABLE_INGREDIENT);
    GetDataFromTable(TABLE_SAUCE);
    GetDataFromTable(TABLE_TASTE);

    SelectUserIDFromDB();
    InsertUserPreference();
}

const DBMapType& DBManager::GetTableMap(TableType tbType) const
{
    switch (tbType)
    {
    case TABLE_NONE:
        break;
    case TABLE_BURGER:
        return _BurgerMap;
    case TABLE_INGREDIENT:
        return _IngredientMap;
    case TABLE_SAUCE:
        return _SauceMap;
    case TABLE_TASTE:
        return _TasteMap;
    case TABLE_SELECTEDBURGER:
        return _SelectedBurgerMap;
    default:
        break;
    }
}

void DBManager::InsertUserNameToDB(std::wstring name)
{
    _UserName = name;
    std::wstring query = L"INSERT INTO users_info(name) VALUE('";
    query += name + L"')";
    Excute((SQLWCHAR*)query.c_str());
}

void DBManager::SelectUserIDFromDB()
{
    int id;
    SQLLEN iID;
    std::wstring query = L"SELECT MAX(id) FROM users_info WHERE name = '";
    query += _UserName + L"'"; 
    SQLExecDirect(_HStmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    if (SQLFetch(_HStmt) != SQL_NO_DATA)
    {
        SQLGetData(_HStmt, 1, SQL_C_ULONG, &id, 0, &iID);
        _UserID = id;
    }

    if (_HStmt) SQLCloseCursor(_HStmt);
}

void DBManager::SelectBurgerByUserInfo()
{
    unsigned int id;
    SQLWCHAR* name;
    SQLLEN iID, iName;

    std::wstring query = L"CALL selectBurgerByUserInfo(";
    query += std::to_wstring(_UserID) + L")";

    SQLExecDirect(_HStmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    while (SQLFetch(_HStmt) != SQL_NO_DATA)
    {
        name = (SQLWCHAR*)malloc(sizeof(SQLWCHAR)* 60);
        SQLGetData(_HStmt, 1, SQL_C_ULONG, &id, 0, &iID);
        SQLGetData(_HStmt, 2, SQL_C_WCHAR, name, 60, &iName);

        _SelectedBurgerMap.insert(std::make_pair(id, name));
    }
    if (_HStmt) SQLCloseCursor(_HStmt);
}

void DBManager::InsertUserPreference()
{
    std::wstring query = L"INSERT INTO user_preference(user_id) VALUE(";
    query += std::to_wstring(DBManager::getInstance().GetUserID()) + L")";
    Excute((SQLWCHAR*)query.c_str());
}

const std::vector<std::string> DBManager::GetBurgerInfo(int burger_id, TableType tbType)
{
    std::vector<std::string> burgerInfoVec;
    std::wstring query = L"SELECT name FROM ";
    std::wstring info;

    SQLWCHAR* name;
    SQLLEN iName;

    switch (tbType)
    {
    case TABLE_NONE:
        break;
    case TABLE_INGREDIENT:
        query += L"ingredient WHERE id IN (SELECT ingredient_id FROM burgeringredient WHERE burger_id = ";
        query += std::to_wstring(burger_id) + L")";
        break;
    case TABLE_SAUCE:
        query += L"sauce WHERE id IN (SELECT sauce_id FROM burgersauce WHERE burger_id = ";
        query += std::to_wstring(burger_id) + L")";
        break;
    case TABLE_TASTE:
        query += L"taste WHERE id IN (SELECT taste_id FROM burgertaste WHERE burger_id = ";
        query += std::to_wstring(burger_id) + L")";
        break;
    default:
        break;
    }
    SQLExecDirect(_HStmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    while (SQLFetch(_HStmt) != SQL_NO_DATA)
    {
        name = (SQLWCHAR*)malloc(sizeof(SQLWCHAR)* 30);
        SQLGetData(_HStmt, 1, SQL_C_WCHAR, name, 30, &iName);

        info = std::wstring(name);

        burgerInfoVec.push_back(std::string(info.begin(),info.end()));
    }
    if (_HStmt) SQLCloseCursor(_HStmt);
    return burgerInfoVec;
}

SQLWCHAR* DBManager::GetBurgerName(int id)
{
    auto burger = _BurgerMap.find(id);
    if (burger != _BurgerMap.end())
    {
        return burger->second;
    }
}

int DBManager::GetBurgerPrice(int burger_id)
{
    int price;
    SQLLEN iPrice;

    std::wstring query = L"SELECT price FROM burger WHERE id = ";
    query += std::to_wstring(burger_id);
    SQLExecDirect(_HStmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    while(SQLFetch(_HStmt) != SQL_NO_DATA)
    {
        SQLGetData(_HStmt, 1, SQL_C_ULONG, &price, 0, &iPrice);
    }
    if (_HStmt) SQLCloseCursor(_HStmt);
    return price;
}

int DBManager::GetBurgerKcal(int burger_id)
{
    int kcal;
    SQLLEN iKcal;

    std::wstring query = L"SELECT kcal FROM burger WHERE id = ";
    query += std::to_wstring(burger_id);
    SQLExecDirect(_HStmt, (SQLWCHAR*)query.c_str(), SQL_NTS);

    while (SQLFetch(_HStmt) != SQL_NO_DATA)
    {
        SQLGetData(_HStmt, 1, SQL_C_ULONG, &kcal, 0, &iKcal);
    }
    if (_HStmt) SQLCloseCursor(_HStmt);
    return kcal;
}

void DBManager::DecideBurgerToDB(int burger_id)
{
    std::wstring query = L"UPDATE users_info SET selectBurger_id = ";
    query += std::to_wstring(burger_id) + L" WHERE id = ";
    query += std::to_wstring(_UserID);
    Excute((SQLWCHAR*)query.c_str());
}
