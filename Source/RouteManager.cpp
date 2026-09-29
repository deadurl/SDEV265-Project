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
    
    std::cout << "Routing..." << std::endl;

    //set the base directory for mustache
    crow::mustache::set_global_base("View");

    
    // Login page
    CROW_ROUTE(_app, "/login")
    ([]() {
        crow::mustache::template_t ret =
        crow::mustache::load("login.html");

        return ret.render();
    });

    // Login submission
    CROW_ROUTE(_app, "/login").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req) {

        auto params = req.get_body_params();

        auto username = params.get("username");
        auto password = params.get("password");

        if (username && password &&
            std::string(username) == "testusername" &&
            std::string(password) == "testpassword") {

            crow::response res;
            res.code = 302;
            res.set_header("Location", "/finance");
            return res;
        }

        return crow::response(401, "Invalid username or password");
    });

    // Finance page
    CROW_ROUTE(_app, "/finance")
    ([]() {
        crow::mustache::template_t ret =
            crow::mustache::load("index.html");

        return ret.render();
    });
    
    // Main page
    CROW_ROUTE(_app, "/")
    ([this]() {
        crow::mustache::template_t ret =
            crow::mustache::load("login.html");

        return ret.render();
    });

    // CSS file
    CROW_ROUTE(_app, "/finance.css")
    ([]() {
        std::string css =
            crow::mustache::load_text("finance.css");

        crow::response res(css);
        res.set_header("Content-Type", "text/css");

        return res;
    });

    // Other pages
    CROW_ROUTE(_app, "/<string>")
    ([this](std::string page) {

        crow::mustache::template_t ret =
            crow::mustache::load("error.html");

        int fun = _Route(page);

        if (fun > -1) {
            auto cont = _fun[fun];

            if (cont.call != nullptr)
                cont.call();

            ret = crow::mustache::load(cont.HTML_Pth);
        }

        return ret.render();
    });
}

void RouteManager::Run(int port) {
    _app.port(port).run();
}

RouteManager::RouteManager() {
    std::ifstream file("routing.txt");
    char HTTPty;
    Requests * req;

    for (int i = 0; file; i++) {
        file >> _routes[i] >> _fun[i].HTML_Pth >> HTTPty;
        ++_len;

        if (HTTPty == 'N') {
            _fun[i].call = nullptr;
            continue;
        }
        else if (HTTPty == (char)Requests::RequestType::GET)
            req = new RequestsGet();
        else if (HTTPty == (char)Requests::RequestType::DEL)
            req = new RequestsDelete();
        else if (HTTPty == (char)Requests::RequestType::POST)
            req = new RequestsPost();

        _fun[i].call = req->NextFunc();
    }

    file.close();

    //crow route set
    Route();
}