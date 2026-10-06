#pragma once

#include "Header.h"
#include "Requests.h"
#include "DatabaseManager.h"
#include "M_BaseModel.h"

class M_Transaction : public Requests, public BaseModel
{
private:
    std::string _description;
    std::string _amount;
    std::string _type;

public:
    M_Transaction();
    M_Transaction(std::string description, std::string amount, std::string type);
    M_Transaction(crow::json::wvalue json);

    void SetData(std::string description, std::string amount, std::string type);
    bool Process(DatabaseManager& dbMgr);

    std::vector<std::vector<std::string>> GetHistory(DatabaseManager& dbMgr); 
};