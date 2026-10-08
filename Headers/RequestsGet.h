#pragma once

#include "Header.h"
#include "Requests.h"
#include "DatabaseManager.h"

class RequestsGet : public Requests
{
public:
    std::vector<std::vector<std::string>> GetHistory(DatabaseManager& dbMgr);
    std::string GetBalance(DatabaseManager& dbMgr);
};