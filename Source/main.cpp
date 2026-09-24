#include <iostream>
#include <crow.h>
#include "DatabaseManager.h"

int main()
{
    std::cout << "SDEV265 Project is working!" << std::endl;

    DatabaseManager database;

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]()
    {
        return "Hello from Crow!";
    });

    app.port(18080).multithreaded().run();

    return 0;
}