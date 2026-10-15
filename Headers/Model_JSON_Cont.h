#pragma once

#include "Header.h"
#include <optional>

template <class T>
class Model_JSON_Cont {
    std::optional<T> _model;
    crow::json::wvalue _json;
    std::string _strRep;

public:
    Model_JSON_Cont(std::string);
    Model_JSON_Cont(crow::json::wvalue sql)
        : _strRep(sql.dump()), _json(sql) {}
    
    std::optional<T> GetModel();
    crow::json::wvalue GetJson();
    std::string GetString();

    //shhh... your time will come :>
    friend crow::json::wvalue::list ChangeArrayType(std::vector<Model_JSON_Cont<EMPTY>>);

};