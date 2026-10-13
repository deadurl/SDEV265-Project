
#include <iostream>
#include <filesystem>
#include "RouteManager.h"

int main()
{
    std::cout << "SDEV265 Project is working!" << std::endl;

    // Find the folder containing the executable.
    std::filesystem::path exePath =
        std::filesystem::absolute(".");

    // Change to the project root when launched from build.
    if (std::filesystem::exists("build/SDEV265-Project.exe"))
    {
        exePath = std::filesystem::current_path();
    }
    else if (std::filesystem::exists("../View"))
    {
        exePath = std::filesystem::current_path().parent_path();
    }

    std::filesystem::current_path(exePath);

    crow::mustache::set_global_base("View");

    RouteManager routes;
    routes.Run(18080);

    return 0;
}
