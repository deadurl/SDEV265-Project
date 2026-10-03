#pragma once

#include "Header.h"

class RouteManager {
    struct FileFunContainer {
        std::string HTML_Pth;
        std::function<bool()> call;
    };
    std::vector<FileFunContainer> _fun;
    std::vector<std::string> _routes;

    crow::SimpleApp _app;
    
    int _Route(std::string);
public:
    void Route();
    void Run(int);

    RouteManager();
};