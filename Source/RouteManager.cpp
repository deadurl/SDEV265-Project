#include "RouteManager.h"

std::function<bool()> RouteManager::_Route(std::string route) {
    if (route == _routes[0]) {
        //return 
    }
}

void RouteManager::Route() {
    // hopefully this allows for the css to be included
    crow::mustache::set_global_base("./View");

    for (int i = 0; i < ROUTES; i++) {
        CROW_ROUTE(_app, "/{}"})([i, this](std::string ){
            if (!_Route(_routes[i]))
                return "error";
            auto ret = crow::mustache::load(pths[i].HTMLpth);
            return ret.render();
        });
    }
}

void RouteManager::SetPort(int port) {
    _app.port(port).run();
}