#include "M_Transaction.h"

M_Transaction::M_Transaction()
{
}

M_Transaction::M_Transaction(std::string description, std::string amount, std::string type)
{
    _description = description;
    _amount = amount;
    _type = type;
}

M_Transaction::M_Transaction(crow::json::wvalue json)
    : BaseModel(json)
{
}

void M_Transaction::SetData(std::string description, std::string amount, std::string type)
{
    _description = description;
    _amount = amount;
    _type = type;
}

bool M_Transaction::Process(DatabaseManager& dbMgr)
{
    std::cout << "Description: " << _description << std::endl;
    std::cout << "Amount: " << _amount << std::endl;
    std::cout << "Type: " << _type << std::endl;

    return true;
}