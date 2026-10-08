#include "RequestsDelete.h"

bool RequestsDelete::DeleteTransaction(DatabaseManager& dbMgr, std::string id, std::string type)
{
    std::string sql;

    if (type == "expense")
    {
        sql =
            "DELETE FROM EXPENSE "
            "WHERE EXP_ID = " + id;
    }
    else if (type == "income")
    {
        sql =
            "DELETE FROM BUDGET "
            "WHERE BUD_ID = " + id;
    }
    else
    {
        return false;
    }

    dbMgr.SQL_STMT(sql);

    return true;
}