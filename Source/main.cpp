#include <iostream>
#include <crow.h>
#include "DatabaseManager.h"

int main()
{
    std::cout << "SDEV265 Project is working!" << std::endl;

    crow::SimpleApp app;

    // Main webpage
    CROW_ROUTE(app, "/")
    ([]()
    {
        crow::response res;
        res.set_static_file_info("View/index.html");
        return res;
    });

    // CSS file
    CROW_ROUTE(app, "/finance.css")
    ([]()
    {
        crow::response res;
        res.set_static_file_info("View/finance.css");
        return res;
    });

    app.port(18080).multithreaded().run();

    return 0;
}