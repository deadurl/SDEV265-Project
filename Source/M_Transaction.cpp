#include "M_Transaction.h"

void M_Transaction::SetData(std::string description, std::string amount, std::string type)
{
    _description = description;
    _amount = amount;
    _type = type;
}

bool M_Transaction::Process(DatabaseManager& dbMgr)
{
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
