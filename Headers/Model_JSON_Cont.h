#pragma once

#include "Header.h"

template <class T>
class Model_JSON_Cont {
    std::optional<T> _model;
    crow::json::wvalue _json;
public:
    crow::json::wvalue GetJson();
    std::optional<T> GetModel();
    //method to generate models and jsons from string returned by sqlite3
    Model_JSON_Cont(std::string); 
};


