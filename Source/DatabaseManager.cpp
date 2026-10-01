#include "DatabaseManager.h"

namespace {
// dono if callback works this way or not 
// TODO: test
static int callback(void* columns, int argc, char** argv, char** colNam) {
    std::vector<std::string> * col = (std::vector<std::string>*)columns;
    std::stringstream ss;

    for (int i = 0; i < argc; ++i) {
        ss << colNam[i] << ' ' << argv[i] << '\n';   
    }
    col->push_back(ss.str());
    return 0;
}

}

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

    //create templates for _SubVarsInTemplate()
    _sqlStatementTemplates.push_back("SELECT * FROM ?"); //0 - select
    _sqlStatementTemplates.push_back("INSERT INTO USER VALUES(?)"); //1 - insert
    _sqlStatementTemplates.push_back("INSERT INTO BUDGET VALUES(?)"); //2
    _sqlStatementTemplates.push_back("INSERT INTO EXPENSE VALUES(?)"); //3
    _sqlStatementTemplates.push_back("INSERT INTO ALERT VALUES(?)"); //4


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
        statement.replace(position, variable.length(), value); //this wont work
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

//this would be for returning lists of columns
template<class T>
std::vector<Model_JSON_Cont<T>> DatabaseManager::SQL_STMT(int index, std::string value) {
    std::vector<Model_JSON_Cont<T>> ret;
    std::vector<std::string> columns;

    // put this in new func
    std::string statement = _SubVarsInTemplate(index, value);

    if (statement.empty())
    {
        std::cout << "SQL statement was not found." << std::endl;
        throw;
    }

    char* errorMessage = nullptr;

    int result = sqlite3_exec(_db, statement.c_str(), callback, &columns, &errorMessage);
    // put above in new func

    if (result != SQLITE_OK)
    {
        std::cout << "SQL Error: "
                  << errorMessage << std::endl;

        sqlite3_free(errorMessage);
    }

    for (auto col : columns) 
        ret.push_back(new Model_JSON_Cont<T>(col));

    return ret;

}

bool DatabaseManager::SQL_isERR()
{
    if (_db == nullptr)
    {
        return true;
    }

    return sqlite3_errcode(_db) != SQLITE_OK;
}