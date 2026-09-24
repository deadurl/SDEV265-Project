#pragma once

#include "Header.h"
#include "DatabaseManager.h"

class Requests {
public:
    const static enum class RequestType : char { GET = 'G', POST = 'P', DEL = 'D' };
private:
    DatabaseManager _dbMgr;
    RequestType _ty;
    std::function<bool()> * _fun;
    unsigned int _next;

public:
    std::function<bool()> NextFunc();

    Requests() : _next(0) {}
};