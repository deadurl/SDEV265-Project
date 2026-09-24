#include "RouteManager.h"

#include "RequestsGet.h"
#include "RequestsPost.h"
#include "RequestsDelete.h"

int RouteManager::_Route(std::string route) {
    for (int i = 0; i < _len; i++) {
        if (_routes[i] == route) {
            return i;
        }
    }
    return -1;
}

void RouteManager::Route() {
    // hopefully this allows for the css to be included
    crow::mustache::set_global_base("View");

    // todo: change this into "/<path>"
    CROW_ROUTE(_app, "/<string>") ([this](std::string page) {
        //landing page load, ret must be initialized (static so called once)
        crow::mustache::template_t ret = crow::mustache::load("index.html");
        int fun = 0;
        for (int i = 0; i < _len; i++) {
            fun = _Route(_routes[i]);
            // default page should be index.html
            if (fun > -1) {
                auto cont = _fun[i];
                if (cont.call != nullptr)
                    cont.call(); 
                ret = crow::mustache::load(cont.HTML_Pth);
            } else {
                ret = crow::mustache::load("error.html");
            }
            return ret.render();
        }
    });
}

void RouteManager::Run(int port) {
    _app.port(port).run();
}

RouteManager::RouteManager() {
    std::ifstream file("routing.txt");
    char HTTPty;
    Requests * req; 

    for (int i = 0; !file; i++) {
        file >> _routes[i] >> _fun[i].HTML_Pth >> HTTPty;
        ++_len;
        if (HTTPty == 'N') {
            _fun[i].call = nullptr;
            continue;
        } else if (HTTPty == (char)Requests::RequestType::GET)
            req = new RequestsGet();
        else if (HTTPty == (char)Requests::RequestType::DEL)
            req = new RequestsDelete();
        else if (HTTPty == (char)Requests::RequestType::POST)
            req = new RequestsPost();

        _fun[i].call = req->NextFunc();
    }
}
