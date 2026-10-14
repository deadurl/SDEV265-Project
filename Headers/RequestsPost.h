#pragma once

#include "Header.h"
#include "DatabaseManager.h"
#include "M_Transaction.h"

struct RequestsPost 
{
    bool ProcessTransaction(
        DatabaseManager& dbMgr,
        std::string description,
        std::string amount,
        std::string type
    );
};