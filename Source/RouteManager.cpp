#include "RouteManager.h"

#include "RequestsGet.h"
#include "RequestsPost.h"
#include "RequestsDelete.h"
#include "Model_JSON_Cont.h"

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

    RequestsGet getRequest;
    RequestsPost postRequest;
    RequestsDelete deleteRequest;

    //set the base directory for mustache
    crow::mustache::set_global_base("View");

    
// Main page
CROW_ROUTE(_app, "/")
([]() {
    crow::mustache::template_t ret =
        crow::mustache::load("login.html");

    return ret.render();
});

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
        std::string(username) == "CatAdministrator" &&
        std::string(password) == "MeowMeowMeow") {

        crow::response res;
        res.code = 302;
        res.set_header("Location", "/finance");

        return res;
    }

    return crow::response(401, "Invalid username or password");
});

// Finance page
CROW_ROUTE(_app, "/finance")
([this]() {

    RequestsGet getRequest;

    auto history = getRequest.GetHistory(_dbMgr);
    auto balance = getRequest.GetBalance(_dbMgr);

    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    std::stringstream date;
    date << std::setfill('0')
         << std::setw(2) << localTime->tm_mon + 1
         << "/"
         << std::setw(2) << localTime->tm_mday
         << "/"
         << localTime->tm_year + 1900;

    crow::mustache::context ctx;

    crow::json::wvalue::list historyList;

    for (auto row : history)
    {
        crow::json::wvalue entry;

        entry["date"] = row[0];
        entry["description"] = row[1];
        entry["amount"] = row[2];
        entry["type"] = row[3];

        historyList.push_back(std::move(entry));
    }

    ctx["history"] = std::move(historyList);
    ctx["balance"] = balance;
    ctx["date"] = date.str();

    crow::mustache::template_t ret =
        crow::mustache::load("index.html");

    return ret.render(ctx);
});


CROW_ROUTE(_app, "/finance").methods(crow::HTTPMethod::POST)
([this](const crow::request& req) {

    auto params = req.get_body_params();

    auto description = params.get("description");
    auto amount = params.get("amount");
    auto type = params.get("type");

    if (description && amount && type)
    {
        RequestsPost postRequest;

        postRequest.ProcessTransaction(
            _dbMgr,
            std::string(description),
            std::string(amount),
            std::string(type)
        );
    }

    crow::response res;
    res.code = 302;
    res.set_header("Location", "/finance");

    return res;
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

    /*// Other pages
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
    });*/
}

void RouteManager::Run(int port) {
    _app.port(port).run();
}

RouteManager::RouteManager()
{
    _len = 0;

    _fun = new FileFunContainer[10];
    _routes = new std::string[10];

    std::ifstream file("routing.txt");
    char HTTPty;
    Requests* req;

    for (int i = 0; file && i < 10; i++)
    {
        file >> _routes[i] >> _fun[i].HTML_Pth >> HTTPty;

        if (!file)
            break;

        ++_len;

        if (HTTPty == 'N')
        {
            _fun[i].call = nullptr;
            continue;
        }
        else if (HTTPty == (char)Requests::RequestType::GET)
            req = new RequestsGet();
        else if (HTTPty == (char)Requests::RequestType::DEL)
            req = new RequestsDelete();
        else if (HTTPty == (char)Requests::RequestType::POST)
            req = new RequestsPost();
        else
            req = nullptr;

        if (req != nullptr)
            _fun[i].call = req->NextFunc();
        else
            _fun[i].call = nullptr;
    }

    file.close();

    Route();
}   