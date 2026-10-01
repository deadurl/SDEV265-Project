#pragma once

#include "Header.h"

template <class T>
class Model_JSON_Cont {
    T _model;
    crow::json::wvalue _json;
public:
    crow::json::wvalue GetJson();
    T GetModel();
    //method to generate models and jsons from string returned by sqlite3
    Model_JSON_Cont(std::string); 
};


