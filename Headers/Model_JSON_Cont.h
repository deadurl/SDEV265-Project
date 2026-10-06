#pragma once

#include "Header.h"
#include <optional>

template <class T>
class Model_JSON_Cont
{
    std::optional<T> _model;
    crow::json::wvalue _json;

public:
    Model_JSON_Cont(std::string sql);
    Model_JSON_Cont(T model);

    std::optional<T> GetModel();
    crow::json::wvalue GetJson();
};