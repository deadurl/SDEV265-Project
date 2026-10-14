#pragma once

#include "Header.h"
#include "DatabaseManager.h"

struct RequestsGet 
{
    std::vector<std::vector<std::string>> GetHistory(DatabaseManager& dbMgr);
    std::string GetBalance(DatabaseManager& dbMgr);
};