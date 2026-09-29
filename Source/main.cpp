#include <iostream>
#include "RouteManager.h"

int main()
{
    std::cout << "SDEV265 Project is working!" << std::endl;

    RouteManager routes;
    routes.Run(18080);

    return 0;
}