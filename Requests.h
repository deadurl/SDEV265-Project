#pragma once

#include "Header.h"
#include "DatabaseManager.h"

class Requests {
public:
    const static enum RequestType { GET, POST, DEL };
private:
    DatabaseManager _dbMgr;
    RequestType _ty;
public:
    Requests(); //mabe dont need this?
};