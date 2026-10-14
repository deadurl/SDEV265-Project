#pragma once

#include "Header.h"
#include "DatabaseManager.h"

//should only be 1 instance of this running
class RouteManager {
    DatabaseManager _dbMgr;
    crow::SimpleApp _app;
public:
    void Route();
    void Run(int);
};