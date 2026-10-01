#include <iostream>
#include <crow.h>
#include <sqlite3.h>
#include <fstream>
#include <vector>
#include <sstream>

template <class T>
class Model_JSON_Cont {
    T _model;
    crow::json::wvalue _json;
public:
    crow::json::wvalue GetJson();
    T GetModel();
    //method to generate models and jsons from string returned by sqlite3
    Model_JSON_Cont(std::string); 
};

struct EMPTY {
};


static int callback(void* columns, int argc, char** argv, char** colNam) {
    std::vector<std::string> * col = (std::vector<std::string>*)columns;
    std::stringstream ss;

    for (int i = 0; i < argc; ++i) {
        ss << colNam[i] << ' ' << argv[i] << '\n';   
        std::cout << colNam[i] << '=' << argv[i];
    }
    col->push_back(ss.str());
    return 0;
}

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

    //_model = new T(_json);
}

int main() {
    sqlite3 * _db;
    int result = sqlite3_open("budget.db", &_db);

    if (result != SQLITE_OK)
    {
        std::cout << "Could not open database." << std::endl;
    }
    else
    {
        std::cout << "Database opened successfully!" << std::endl;
    }
    const char* sql =
        "CREATE TABLE IF NOT EXISTS USER ("
        "USER_ID INTEGER PRIMARY KEY,"
        "USER_UNAME TEXT NOT NULL,"
        "USER_PWORD TEXT NOT NULL"
        ");"

        "CREATE TABLE IF NOT EXISTS BUDGET ("
        "BUD_ID INTEGER PRIMARY KEY,"
        "USER_ID INTEGER NOT NULL,"
        "BUD_VAL REAL NOT NULL,"
        "BUD_DATE TEXT NOT NULL,"
        "BUD_DESC TEXT,"
        "FOREIGN KEY(USER_ID) REFERENCES USER(USER_ID)"
        ");"

        "CREATE TABLE IF NOT EXISTS EXPENSE ("
        "EXP_ID INTEGER PRIMARY KEY,"
        "USER_ID INTEGER NOT NULL,"
        "EXP_VAL REAL NOT NULL,"
        "EXP_DATE TEXT NOT NULL,"
        "EXP_DESC TEXT,"
        "FOREIGN KEY(USER_ID) REFERENCES USER(USER_ID)"
        ");"

        "CREATE TABLE IF NOT EXISTS ALERT ("
        "AL_ID INTEGER PRIMARY KEY,"
        "AL_USER_ID INTEGER NOT NULL,"
        "AL_DESC TEXT,"
        "FOREIGN KEY(AL_USER_ID) REFERENCES USER(USER_ID)"
        ");";

    char* errorMessage = nullptr;

    result = sqlite3_exec(_db, sql, nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK)
    {
        std::cout << "Error creating tables: "
                  << errorMessage << std::endl;

        sqlite3_free(errorMessage);
    }
    else
    {
        std::cout << "Database tables created successfully!" << std::endl;
    }
    //to test
    std::vector<Model_JSON_Cont<EMPTY>> ret;
    std::vector<std::string> columns;
/*
std::string additions = "INSERT INTO USER VALUES (NULL, \"username\", \"password\");"
"INSERT INTO USER VALUES (NULL, \"uname\", \"pword\")";

result = sqlite3_exec(_db, additions.c_str(), nullptr, nullptr, &errorMessage);

if (result != SQLITE_OK)
{
    std::cout << "SQL Error: "
    << errorMessage << std::endl;
    
    sqlite3_free(errorMessage);
}
*/

    result = sqlite3_exec(_db, "SELECT * FROM USER", callback, &columns, &errorMessage);

    if (result != SQLITE_OK)
    {
        std::cout << "SQL Error: "
                  << errorMessage << std::endl;

        sqlite3_free(errorMessage);
    }

    std::cout << std::endl;

    for (auto col : columns) {
        ret.push_back(Model_JSON_Cont<EMPTY>(col));
        std::cout << col << std::endl;
    }

}

/*
int main()
{
    std::string route;
    std::string path;
    std::stringstream ss;
    char HTTPty;
    std::ifstream file("./Util/routing.txt");

    if (!file.is_open())
        std::cout << "ERR :(" << std::endl; // mabe throw

    while (std::getline(file, route)) {
        std::cout << route << std::endl;
        ss << route;
        ss >> route >> path >> HTTPty;
    }
    
    file.close();
    return -1;
    
    std::cout << '-' << path << std::endl;

    crow::SimpleApp app;

    crow::mustache::set_global_base("Template");

    CROW_ROUTE(app, "/<string>")([route, path](std::string str)
    {
        auto ret = crow::mustache::load("index.html");
        if (str == route)
            auto ret = crow::mustache::load(path);

        return ret.render();
    });
    

    app.port(18080).multithreaded().run();

    return 0;
}
*/