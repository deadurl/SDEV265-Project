#pragma once

#include "Header.h"

template <class T>
class Model_JSON_Cont {
    T _model;
    crow::json::rvalue _json;
public:
    void GetJson();
    T getModel();
};