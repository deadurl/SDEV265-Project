#include "Model_JSON_Cont.h"
#include "M_BaseModel.h"
#include "M_Transaction.h"

template <class T>
std::optional<T> Model_JSON_Cont<T>::GetModel()
{
    if (_model.has_value())
        return _model;

    return {};
}

template <class T>
crow::json::wvalue Model_JSON_Cont<T>::GetJson()
{
    return _json;
}

template <class T>
Model_JSON_Cont<T>::Model_JSON_Cont(std::string sql)
{
    std::stringstream ss0(sql), ssN;
    std::string val;
    std::string ele;

    while (std::getline(ss0, val))
    {
        ssN << val;
        ssN >> val >> ele;
        _json[val] = ele;
    }

    if constexpr (std::is_same_v<T, EMPTY>)
        return;
    else if constexpr (std::is_base_of_v<BaseModel, T>)
        _model = T(_json);
}

template <class T>
Model_JSON_Cont<T>::Model_JSON_Cont(T model)
{
    _model = model;
}

template class Model_JSON_Cont<M_Transaction>;