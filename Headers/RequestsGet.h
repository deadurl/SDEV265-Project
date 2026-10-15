#pragma once

#include "Header.h"
#include "DatabaseManager.h"
#include "Model_JSON_Cont.h"

struct RequestsGet 
{
    std::vector<std::vector<std::string>> GetHistory(DatabaseManager& dbMgr);
    std::vector<Model_JSON_Cont<EMPTY>> GetHistoryMJC(DatabaseManager& dbMgr);
    std::string GetBalance(DatabaseManager& dbMgr);
};