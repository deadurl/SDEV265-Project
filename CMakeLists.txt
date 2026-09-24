cmake_minimum_required(VERSION 3.10)

project(SDEV265-Project)

find_package(Crow CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

add_executable(SDEV265-Project Source/main.cpp Source/DatabaseManager.cpp)

target_include_directories(SDEV265-Project PRIVATE Headers)
target_link_libraries(SDEV265-Project PRIVATE Crow::Crow unofficial::sqlite3::sqlite3 ws2_32 mswsock)