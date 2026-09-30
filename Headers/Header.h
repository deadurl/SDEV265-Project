#pragma once

#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include <sstream>

#include <crow.h>
//#include 
// include the other files here

// thrown types
struct FILE_ERR {
    std::string MSG;
    std::ifstream *FS;
    FILE_ERR(std::string msg, std::ifstream* fs) : MSG(msg), FS(fs) {}
};

//dumb types (this is probably mabe used dont delete)
struct EMPTY {
};