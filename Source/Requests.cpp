#include "Requests.h"

Requests::Requests()
{
    _next = 0;

    _fun = new std::function<bool()>[10];

    for (int i = 0; i < 10; i++)
        _fun[i] = nullptr;
}

std::function<bool()> Requests::NextFunc()
{
    if (_fun[_next] == nullptr)
        return nullptr;

    return _fun[_next++];
}