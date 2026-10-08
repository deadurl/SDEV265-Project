#include "RequestsPost.h"

bool RequestsPost::ProcessTransaction(
    DatabaseManager& dbMgr,
    std::string description,
    std::string amount,
    std::string type)
{
    M_Transaction transaction(description, amount, type);

    return transaction.Process(dbMgr);
}