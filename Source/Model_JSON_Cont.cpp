#include "Model_JSON_Cont.h"
#include "BaseModel.h"

//will return empty if there is no model
template <class T>
std::optional<T> Model_JSON_Cont<T>::GetModel() {
    if (_model.isInitialized())
        return _model;
    return {};
}

template<class T>
crow::json::wvalue Model_JSON_Cont<T>::GetJson() {
    return _json;
}

template<class T>
Model_JSON_Cont<T>::Model_JSON_Cont(std::string sql) {
    std::stringstream ss0(sql), ssN;
    std::string val;
    std::string ele;

    while (std::getline(ss0, val)) {
        ssN << val;
        ssN >> val >> ele;
        _json[val] = ele;
    }

    // dono if this will ever be used (has bad bloat) but i dono if the model will be used either
    if constexpr (std::is_same_v<T, EMPTY>) 
        return;
    else if constexpr (std::is_base_of_v<BaseModel, T>)
        _model = new T(_json);
}