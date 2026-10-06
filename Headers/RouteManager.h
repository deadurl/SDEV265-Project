#pragma once

#include <string>
#include <functional>
#include <crow.h>

class RouteManager {
    struct FileFunContainer {
        std::string HTML_Pth;
        std::function<bool(const crow::request&, const crow::response&)> call;
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