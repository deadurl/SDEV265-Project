#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager()
{
    _db = nullptr;

    int result = sqlite3_open("budget.db", &_db);

    if (result != SQLITE_OK)
    {
        std::cout << "Could not open database." << std::endl;
    }
    else
    {
        std::cout << "Database opened successfully!" << std::endl;
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS USER ("
        "USER_ID INTEGER PRIMARY KEY,"
        "USER_UNAME TEXT NOT NULL,"
        "USER_PWORD TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS BUDGET ("
        "BUD_ID INTEGER PRIMARY KEY,"
        "USER_ID INTEGER NOT NULL,"
        "BUD_VAL REAL NOT NULL,"
        "BUD_DATE TEXT NOT NULL,"
        "BUD_DESC TEXT,"
        "FOREIGN KEY(USER_ID) REFERENCES USER(USER_ID)"
        ");"

        "CREATE TABLE IF NOT EXISTS EXPENSE ("
        "EXP_ID INTEGER PRIMARY KEY,"
        "USER_ID INTEGER NOT NULL,"
        "EXP_VAL REAL NOT NULL,"
        "EXP_DATE TEXT NOT NULL,"
        "EXP_DESC TEXT,"
        "FOREIGN KEY(USER_ID) REFERENCES USER(USER_ID)"
        ");"

        "CREATE TABLE IF NOT EXISTS ALERT ("
        "AL_ID INTEGER PRIMARY KEY,"
        "AL_USER_ID INTEGER NOT NULL,"
        "AL_DESC TEXT,"
        "FOREIGN KEY(AL_USER_ID) REFERENCES USER(USER_ID)"
        ");";

    char* errorMessage = nullptr;

    result = sqlite3_exec(_db, sql, nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK)
    {
        std::cout << "Error creating tables: "
                  << errorMessage << std::endl;

        sqlite3_free(errorMessage);
    }
    else
    {
        std::cout << "Database tables created successfully!" << std::endl;
    }
}

DatabaseManager::~DatabaseManager()
{
    if (_db != nullptr)
    {
        sqlite3_close(_db);
    }
}

std::string DatabaseManager::_SubVarsInTemplate(int index, std::string value)
{
    if (index < 0 || index >= _sqlStatementTemplates.size())
    {
        return "";
    }

    std::string statement = _sqlStatementTemplates[index];

    std::string variable = "?";

    size_t position = statement.find(variable);

    if (position != std::string::npos)
    {
        statement.replace(position, variable.length(), value);
    }

    return statement;
}

void DatabaseManager::SQL_STMT(int index, std::string value)
{
    std::string statement = _SubVarsInTemplate(index, value);

    if (statement.empty())
    {
        std::cout << "SQL statement was not found." << std::endl;
        return;
    }

    char* errorMessage = nullptr;

    int result = sqlite3_exec(_db, statement.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK)
    {
        std::cout << "SQL Error: "
                  << errorMessage << std::endl;

        sqlite3_free(errorMessage);
    }
}

bool DatabaseManager::SQL_isERR()
{
    if (_db == nullptr)
    {
        return true;
    }

    return sqlite3_errcode(_db) != SQLITE_OK;
}