#include "RouteManager.h"

#include "RequestsGet.h"
#include "RequestsPost.h"
#include "RequestsDelete.h"

void RouteManager::Route() {
    RequestsGet getRequest;
    RequestsPost postRequest;
    RequestsDelete deleteRequest;

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
        
        auto balance = getRequest.GetBalance(_dbMgr);
        time_t now = time(nullptr);
        tm* localTime = localtime(&now);

        std::stringstream date;
        date << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");

        crow::mustache::context ctx;
        ctx["history"] = std::move(ChangeArrayType(getRequest.GetHistoryMJC(_dbMgr)));
        ctx["balance"] = balance;
        ctx["date"] = date.str();

        return crow::mustache::load("index.html").render(ctx);
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

    // Delete transaction
    CROW_ROUTE(_app, "/finance/delete")
    .methods(crow::HTTPMethod::POST)
    ([this](const crow::request& req) {

    auto params = req.get_body_params();

    auto id = params.get("id");
    auto type = params.get("type");

    if (id && type)
    {
        RequestsDelete deleteRequest;

        deleteRequest.DeleteTransaction(
            _dbMgr,
            std::string(id),
            std::string(type)
        );
    }

    crow::response res;
    res.code = 302;
    res.set_header("Location", "/finance");

    return res;
    });
}

void RouteManager::Run(int port) {
    _app.port(port).run();
}
