#include <iostream>
#include <crow.h>

int main()
{
    std::string route;
    std::string path;
    std::function<bool()> func;
    std::stringstream ss;
    char HTTPty;
    std::ifstream file ("routing.txt");

    if (!file.is_open())
        std::cout << "??? it reads later??? :( " << std::endl; // mabe throw

    while (std::getline(file, route)) {
        ss.str() = route;
        ss >> route >> path >> HTTPty;
    }
    

    crow::SimpleApp app;

    CROW_ROUTE(app, "/<string>")([route, path](std::string str)
    {
        auto ret = crow::mustache::load("index.html");
        if (str == route)
            auto ret = crow::mustache::load(path);

        return ret.render();
    });
    

    app.port(18080).multithreaded().run();

    return 0;
}