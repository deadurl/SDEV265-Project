#include "RouteManager.h"

#include "RequestsGet.h"
#include "RequestsPost.h"
#include "RequestsDelete.h"

#include <iostream>

// thrown types
namespace {
    struct FILE_ERR {
        std::string MSG;
        std::ifstream *FS;
        FILE_ERR(std::string msg, std::ifstream* fs) : MSG(msg), FS(fs) {}
    };
};

int RouteManager::_Route(std::string route) {
    for (int i = 0; i < _fun.size(); i++) {
        std::cout << _routes[i] << ' ' << route << (_routes[i] == route? " true" : " false") << std::endl;
        if (_routes[i] == route) {
            return i;
        }
    }
    return -1;
}

void RouteManager::Route() {
    // hopefully this allows for the css to be included
    crow::mustache::set_global_base("Template");

    // * static page loading *

    // for landing page
    CROW_ROUTE(_app, "/") ([](){
        crow::mustache::template_t pg = crow::mustache::load("index.html");
        return pg.render();
    });

    // messy for every other page
    // todo: change this into "/<path>"
    CROW_ROUTE(_app, "/<string>") ([this](std::string page) {
        std::string finPage = "error.html";
        int funRet = _Route(page);
        
        if (funRet > -1) {
            auto FFcont = _fun[funRet];
            finPage = FFcont.HTML_Pth;
        }
        std::cout << finPage << std::endl;

        crow::mustache::template_t pg = crow::mustache::load(finPage);
        return pg.render();
    });

    // * specific requests *

    // TODO: work on this
    //i think that with this logic, all of the routes are capable of having a request... sounds bad
    //this is sopposed to be for error handling, but whatever. it should work in theory
    //i think that you can look for crow::request requests in a normal crow route, but running logic to check if there was a non get request (get requests will get pages) and return something different which the compiler was not happy with :(
    /*
    CROW_CATCHALL_ROUTE(_app) ([this](const crow::request& req, crow::response& res) {
        std::string nurl = req.url; // to get rid of the '/'

        int funRet = _Route(nurl.erase(0, 1));
        std::cout << funRet << std::endl;

        if (funRet == -1) {
            res.code = 404;
            res.end();
            return;
        } 

        auto FFcont = _fun.at(funRet);
            
        if (FFcont.call != nullptr)
            FFcont.call(req, res); 

        res.code = 200;
        res.body = "reload page if needed"; // test this, sometimes the request does not change and you get the default 405 responce :(
        res.add_header("Location", "index");
        res.end();
    });
    */

    CROW_ROUTE(_app, "/<string>").methods(crow::HTTPMethod::POST, crow::HTTPMethod::Delete)
     ([this](const crow::request& req, std::string pth) {
        std::string nurl = req.url; // to get rid of the '/'
        crow::response res;

        int funRet = _Route(nurl.erase(0, 1));
        std::cout << funRet << std::endl;

        if (funRet == -1) {
            res.code = 404;
            return res;
        } 

        auto FFcont = _fun.at(funRet);
            
        if (FFcont.call != nullptr)
            FFcont.call(req, res); 

        res.code = 200;
        res.body = "reload page if needed"; // test this, sometimes the request does not change and you get the default 405 responce :(
        res.add_header("Location", "/index");
        return res;
    });
}

void RouteManager::Run(int port) {
    _app.port(port).run();
}

RouteManager::RouteManager() {
    std::string routeLn;
    std::string path;
    char HTTPty; // TODO: change this to be weather there should be anything loaded from a 
    std::function<bool(const crow::request&, const crow::response&)> func;

    std::stringstream ss;
    Requests * req; 
    std::ifstream file("./Util/routing.txt");
    if (!file.is_open())
        throw FILE_ERR(std::string("file not opening"), &file); // file might be deleted by this point :(

    while (std::getline(file, routeLn)) {
        ss << routeLn;
        ss >> routeLn >> path >> HTTPty;

        _routes.push_back(routeLn);
        
        //get the http request type of each line in routing.txt
        //if the request is sent by the page, then may not need to store the http response
        // TODO: redo this into mabe a switch statement
        if (HTTPty == 'N') {
            _fun.push_back({path, nullptr});
            continue;
        }
        else if (HTTPty == (char)Requests::RequestType::GET)
            req = new RequestsGet();
        else if (HTTPty == (char)Requests::RequestType::DEL)
            req = new RequestsDelete();
        else if (HTTPty == (char)Requests::RequestType::POST)
            req = new RequestsPost();

        func = req->NextFunc();
        _fun.push_back({routeLn, func});
    }

    file.close();
}
