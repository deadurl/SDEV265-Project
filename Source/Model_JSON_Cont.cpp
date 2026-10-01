#include "Model_JSON_Cont.h"

template <class T>
T Model_JSON_Cont<T>::GetModel() {
    return _model;
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
    if constexpr (std::is_same_v<T, EMPTY>) {
        return;
    }

    //i dont think ill need this for the moment
    //_model = new T(_json);
}