#pragma once

#include "Header.h"

#include "DatabaseManager.h"

struct RequestsDelete 
{
    bool DeleteTransaction(DatabaseManager& dbMgr, std::string id, std::string type);
};