#pragma once

#include "Header.h"
#include "Model_JSON_Cont.h"

#include <sqlite3.h>
#include <string>
#include <vector>

class DatabaseManager
{
private:
    sqlite3* _db;

public:
    DatabaseManager();
    ~DatabaseManager();

    //void SQL_STMT(int, std::string);
    void SQL_STMT(std::string);

    std::vector<std::vector<std::string>> SQL_QUERY(std::string);
    std::vector<Model_JSON_Cont<EMPTY>> SQL_QUERY(const char *);
};