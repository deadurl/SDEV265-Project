#include "RouteManager.h"

#include "RequestsGet.h"
#include "RequestsPost.h"
#include "RequestsDelete.h"

int RouteManager::_Route(std::string route) {
    for (int i = 0; i < _fun.size() - 1; i++) {
        if (_routes[i] == route) {
            return i;
        }
    }
    return -1;
}

void RouteManager::Route() {
    // hopefully this allows for the css to be included
    crow::mustache::set_global_base("View");

    // for landing page
    CROW_ROUTE(_app, "/") ([](){
        crow::mustache::template_t pg = crow::mustache::load("index.html");
        return pg.render();
    });

    // messy for every other page
    // todo: change this into "/<path>"
    CROW_ROUTE(_app, "/<string>") ([this](std::string page) {
        //initial page load, ret must be initialized(mabe not to error *slow)
        crow::mustache::template_t pg = crow::mustache::load("error.html");
        int funRet = 0;

        for (int i = 0; i < _fun.size() - 1; i++) {
            funRet = _Route(_routes[i]);
            
            if (funRet > -1) {
                auto FFcont = _fun.at(i);

                if (FFcont.call != nullptr)
                    FFcont.call(); 
                
                pg = crow::mustache::load(FFcont.HTML_Pth);
            } 
            return pg.render();
        }
    });
}

void RouteManager::Run(int port) {
    _app.port(port).run();
}

RouteManager::RouteManager() {
    std::string routeLn;
    std::string path;
    char HTTPty;
    std::function<bool()> func;

    std::stringstream ss;
    Requests * req; 
    std::ifstream file ("routing.txt");

    if (!file.is_open())
        return; // mabe throw

    while (std::getline(file, routeLn)) {
        ss.str() = routeLn;
        ss >> routeLn >> path >> HTTPty;

        _routes.push_back(path);

        //get the http request type of each line in routing.txt
        if (HTTPty == 'N') 
            _fun.push_back({routeLn, nullptr});
        else if (HTTPty == (char)Requests::RequestType::GET)
            req = new RequestsGet();
        else if (HTTPty == (char)Requests::RequestType::DEL)
            req = new RequestsDelete();
        else if (HTTPty == (char)Requests::RequestType::POST)
            req = new RequestsPost();

        func = req->NextFunc();
        _fun.push_back({routeLn, func});
    }
}
