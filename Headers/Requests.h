#pragma once

#include "Header.h"

class Requests {

public:

    enum RequestType { GET, POST, DEL };

private:

    RequestType _ty;
    std::function<bool()>* _fun;
    int _next;

public:

    Requests();
    std::function<bool()> NextFunc();

};