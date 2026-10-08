#pragma once

#include "Header.h"
#include "Requests.h"
#include "DatabaseManager.h"

class RequestsDelete : public Requests
{
public:
    bool DeleteTransaction(DatabaseManager& dbMgr, std::string id, std::string type);
};