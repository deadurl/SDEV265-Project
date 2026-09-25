#include "Model_JSON_Cont.h"

template <class T>
T Model_JSON_Cont<T>::GetModel() {
    return _model;
}

template<class T>
crow::json::rvalue Model_JSON_Cont<T>::GetJson() {
    return _json;
}