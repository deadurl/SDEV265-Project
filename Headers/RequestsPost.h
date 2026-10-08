#pragma once

#include "Header.h"
#include "Requests.h"
#include "DatabaseManager.h"
#include "M_Transaction.h"

class RequestsPost : public Requests
{
public:
    bool ProcessTransaction(
        DatabaseManager& dbMgr,
        std::string description,
        std::string amount,
        std::string type
    );
};