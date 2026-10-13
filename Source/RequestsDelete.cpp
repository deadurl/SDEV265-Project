#include "RequestsDelete.h"

bool RequestsDelete::DeleteTransaction(
    DatabaseManager& dbMgr,
    std::string id,
    std::string type)
{
    int transactionID;

    try
    {
        size_t position;
        transactionID = std::stoi(id, &position);

        if (position != id.length() || transactionID <= 0)
            return false;
    }
    catch (...)
    {
        return false;
    }

    std::string sql;

    if (type == "expense")
    {
        sql =
            "DELETE FROM EXPENSE WHERE EXP_ID = "
            + std::to_string(transactionID);
    }
    else if (type == "income")
    {
        sql =
            "DELETE FROM BUDGET WHERE BUD_ID = "
            + std::to_string(transactionID);
    }
    else
    {
        return false;
    }

    dbMgr.SQL_STMT(sql);

    return true;
}