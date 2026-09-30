#include <iostream>
#include <crow.h>
#include <fstream>


int main()
{
    std::string route;
    std::string path;
    std::stringstream ss;
    char HTTPty;
    std::ifstream file("./Util/routing.txt");

    if (!file.is_open())
        std::cout << "ERR :(" << std::endl; // mabe throw

    while (std::getline(file, route)) {
        std::cout << route << std::endl;
        ss << route;
        ss >> route >> path >> HTTPty;
    }
    
    file.close();
    return -1;
    
    std::cout << '-' << path << std::endl;

    crow::SimpleApp app;

    crow::mustache::set_global_base("Template");

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