#pragma once

#include <functional>
#include <crow.h>

#include "DatabaseManager.h"

class Requests {
public:
    enum class RequestType : char { GET = 'G', POST = 'P', DEL = 'D' };
private:
    static DatabaseManager _dbMgr;
    RequestType _ty;
    std::function<bool(const crow::request&, const crow::response&)> * _fun; //request functions may need information from the request and to change the response in case of an error
    unsigned int _next;

public:
    std::function<bool(const crow::request&, const crow::response&)> NextFunc();

    Requests() : _next(0) {}
    
};