#pragma once

#include "Header.h"
#include "Model_JSON_Cont.h"

#include <sqlite3.h>

class DatabaseManager
{
private:
    sqlite3* _db;

    std::vector<std::string> _sqlStatementTemplates;

    std::string _SubVarsInTemplate(int, std::string);

public:
    DatabaseManager();
    ~DatabaseManager();

    void SQL_STMT(int, std::string);
    template <class T>
    std::vector<Model_JSON_Cont<T>> SQL_STMT(const unsigned int&, const std::string&);

    bool SQL_isERR();
};
