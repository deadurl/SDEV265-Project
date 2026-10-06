#pragma once

#include "Header.h"
#include <sqlite3.h>
#include <string>
#include <vector>

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
    void SQL_STMT(std::string);

    std::vector<std::vector<std::string>> SQL_QUERY(std::string);
    
    bool SQL_isERR();
};