#pragma once

#include "Header.h"

class RouteManager {
    struct FileFunContainer {
        std::string HTML_Pth;
        std::function<bool()> call;
    } * _fun;
    std::string * _routes;
    unsigned int _len;

    crow::SimpleApp _app;
    
    int _Route(std::string);
public:
    void Route();
    void Run(int);

    RouteManager();
};