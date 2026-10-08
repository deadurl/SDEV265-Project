#include "RequestsGet.h"
#include <sstream>
#include <iomanip>

std::vector<std::vector<std::string>> RequestsGet::GetHistory(DatabaseManager& dbMgr)
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

std::string RequestsGet::GetBalance(DatabaseManager& dbMgr)
{
    std::string sql =
        "SELECT "
        "(SELECT COALESCE(SUM(BUD_VAL), 0) FROM BUDGET) - "
        "(SELECT COALESCE(SUM(EXP_VAL), 0) FROM EXPENSE)";

    auto result = dbMgr.SQL_QUERY(sql);

    if (result.empty() || result[0].empty())
    {
        return "0.00";
    }

    double balance = std::stod(result[0][0]);

    std::stringstream formatted;
    formatted << std::fixed << std::setprecision(2) << balance;

    return formatted.str();
}