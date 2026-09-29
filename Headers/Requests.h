
#pragma once

#include "Header.h"

#include "DatabaseManager.h"

class Requests {

public:

    enum RequestType { GET, POST, DEL };

private:

    DatabaseManager _dbMgr;
    RequestType _ty;
    std::function<bool()>* _fun;
    int _next;

public:

    Requests();
    std::function<bool()> NextFunc();

};
