#include "Requests.h"

std::function<bool()> Requests::NextFunc() {
    if (_fun[_next] == nullptr)
        return nullptr;
    return _fun[_next++];
}