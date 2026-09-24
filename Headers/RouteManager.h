#pragma once

#include "Header.h"

#define ROUTES 2

class RouteManager {
    const std::string _pths[] = {"", ""};

    const std::string _routes[ROUTES] = {" ", " "};
    crow::SimpleApp _app;
    //const unsigned int _port;
    
    std::function<bool()> _Route(std::string);
public:
    void Route();
    void SetPort(int);
};