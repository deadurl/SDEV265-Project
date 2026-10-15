#include "Model_JSON_Cont.h"
#include "M_BaseModel.h"
#include "M_Transaction.h"

template <class T>
std::optional<T> Model_JSON_Cont<T>::GetModel() {
    if (_model.has_value())
        return _model;

    return {};
}

template <class T>
crow::json::wvalue Model_JSON_Cont<T>::GetJson() {
    return _json;
}

// must be in format of EXACTLY => key value, this WONT WORK if it is another format
template <class T>
Model_JSON_Cont<T>::Model_JSON_Cont(std::string sql)
    : _strRep(sql) {
    std::stringstream ssN, ss0(sql);
    std::string val;
    std::string ele;

    while (std::getline(ss0, val)) {
        ssN << val;
        ssN >> val >> ele;
        std::cout << val << ':' << ele << std::endl;
        _json[val] = ele;
    }

    if constexpr (std::is_same_v<T, EMPTY>)
        return;
    else if constexpr (std::is_base_of_v<BaseModel, T>)
        _model = T(_json);
}

template <class T>
std::string Model_JSON_Cont<T>::GetString() {
    return _strRep;
}

//for main get request in finance, also this could take in a M_Transaction MJC(what it should do), but it is not nessusary 
crow::json::wvalue::list ChangeArrayType(std::vector<Model_JSON_Cont<EMPTY>> mods) {
    crow::json::wvalue::list ls;
    crow::json::wvalue entry;
    
    if (mods.empty())
        return ls;

    for (auto row : mods) {
        // load json into readable format
        crow::json::rvalue rd = crow::json::load(row._json.dump());
        // sub json into list            
        entry["type"] = rd["TYPE"].s();
        entry["amount"] = rd["BUD_VAL"].s();
        entry["description"] = rd["BUD_DESC"].s();
        entry["date"] = rd["BUD_DATE"].s();
        entry["id"] = rd["BUD_ID"].s();
        
        ls.push_back(std::move(entry));
    }
    
    return ls;
}

template class Model_JSON_Cont<M_Transaction>;
template class Model_JSON_Cont<EMPTY>;