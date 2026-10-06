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

    std::string sql;

    if (_type == "expense")
    {
        sql =
            "INSERT INTO EXPENSE "
            "(USER_ID, EXP_VAL, EXP_DATE, EXP_DESC) VALUES ("
            "1, "
            + _amount +
            ", datetime('now'), '"
            + _description +
            "')";
    }
    else if (_type == "income")
    {
        sql =
            "INSERT INTO BUDGET "
            "(USER_ID, BUD_VAL, BUD_DATE, BUD_DESC) VALUES ("
            "1, "
            + _amount +
            ", datetime('now'), '"
            + _description +
            "')";
    }
    else
    {
        std::cout << "Invalid transaction type." << std::endl;
        return false;
    }

    dbMgr.SQL_STMT(sql);

    std::cout << "Transaction saved to database." << std::endl;

    return true;
}

std::vector<std::vector<std::string>> M_Transaction::GetHistory(DatabaseManager& dbMgr)
{
    std::string sql =
        "SELECT BUD_DATE, BUD_DESC, BUD_VAL, 'income' AS TYPE "
        "FROM BUDGET "
        "UNION ALL "
        "SELECT EXP_DATE, EXP_DESC, EXP_VAL, 'expense' AS TYPE "
        "FROM EXPENSE "
        "ORDER BY 1 DESC";

    return dbMgr.SQL_QUERY(sql);
}