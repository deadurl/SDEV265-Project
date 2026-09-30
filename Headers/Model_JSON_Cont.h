#pragma once

#include "Header.h"

template <class T>
class Model_JSON_Cont {
    T _model;
    crow::json::rvalue _json;
public:
    crow::json::rvalue GetJson();
    T GetModel();
    //method to generate models and jsons from string returned by sqlite3
    Model_JSON_Cont(std::string); 
};


