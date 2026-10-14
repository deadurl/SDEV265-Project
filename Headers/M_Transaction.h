#pragma once

#include "Header.h"
#include "DatabaseManager.h"
#include "M_BaseModel.h"

//not really a model anymore but its ok
class M_Transaction : public BaseModel
{
private:
    std::string _description;
    std::string _amount;
    std::string _type;

public:
    M_Transaction() = default;
    M_Transaction(std::string description, std::string amount, std::string type) 
        : _description(description), _amount(amount), _type(type) {}
    M_Transaction(crow::json::wvalue json)
        : BaseModel(json) {}

    void SetData(std::string description, std::string amount, std::string type);
    bool Process(DatabaseManager& dbMgr);

   
};