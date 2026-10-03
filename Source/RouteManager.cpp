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
        //initial page load, ret must be initialized(mabe not to error *slow)
        // TODO: this needs to be changed, will only ever load error.html <- compiles
        crow::mustache::template_t pg = crow::mustache::load("error.html");
        int funRet = _Route(page);
        
        //dono why i had a for loop here, mabe i shouldnt need to find out
        if (funRet > -1) {
            auto FFcont = _fun.at(funRet);
                 
            pg = crow::mustache::load(FFcont.HTML_Pth);
        }
        return pg.render();
    });

    // * specific requests *

    // TODO: work on this
    //i think that with this logic, all of the routes are capable of having a request... sounds bad
    //this is sopposed to be for error handling, but whatever. it should work in theory
    //i think that you can look for crow::request requests in a normal crow route, but running logic to check if there was a non get request (get requests will get pages) and return something different which the compiler was not happy with :(
    CROW_CATCHALL_ROUTE(_app) ([this](const crow::request& req, crow::response& res) {
        std::string nurl = req.url; // to get rid of the '/'
        int funRet = _Route(nurl.erase(0));

        if (funRet == -1) {
            res.code = 404;
            res.end();
            return;
        } 

        auto FFcont = _fun.at(funRet);
            
        if (FFcont.call != nullptr)
            FFcont.call(); 

        res.code = 200;
        res.body = "reload page if needed"; // test this, sometimes the request does not change and you get the default 405 responce :(
        res.add_header("Location", req.url);
        res.end();
    });
}

void RouteManager::Run(int port) {
    _app.port(port).run();
}

RouteManager::RouteManager() {
    std::string routeLn;
    std::string path;
    char HTTPty;
    std::function<bool(const crow::request&, const crow::response&)> func;

    std::stringstream ss;
    Requests * req; 
    std::ifstream file("./Util/routing.txt");
    if (!file.is_open())
        throw new FILE_ERR(std::string("file not opening"), &file); // file might be deleted by this point :(

    while (std::getline(file, routeLn)) {
        ss << routeLn;
        ss >> routeLn >> path >> HTTPty;

        _routes.push_back(path);

        //get the http request type of each line in routing.txt
        //if the request is sent by the page, then may not need to store the http response
        // TODO: redo this into mabe a switch statement
        if (HTTPty == 'N') {
            _fun.push_back({routeLn, nullptr});
            return;
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
