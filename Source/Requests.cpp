#include "Requests.h"

std::function<bool(const crow::request&, const crow::response&)> Requests::NextFunc() {
    if (_fun[_next] == nullptr)
        return nullptr;
    return _fun[_next++];
}