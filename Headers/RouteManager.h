#pragma once

#include "Header.h"

#define ROUTES 2

class RouteManager {
    struct FileContainer {
        std::string HTML_Pth;
        std::string CSS_Pth;
    } * _pths;

    const std::string _routes[ROUTES] = {" ", " "};
    crow::simpleApp _app;
    //const unsigned int _port;
    
    std::function<bool()> _Route(std::string);
public:
    void Route();
    void SetPort(int);
};