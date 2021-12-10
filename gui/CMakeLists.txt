cmake_minimum_required(VERSION 3.16.3)

project(GUI VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-std=c++17 -g -Wall -pthread)

add_library(database_lib 
            SHARED
            sqlite/create.cpp)   

set(SOURCE_FILES gui_main.cpp
                printing.h printing.cpp
                frame.h frame.cpp
                panel.h panel.cpp 
                dialog.h dialog.cpp
                extern.h extern.cpp
                listviewbox.cpp
                client.cpp
                itemdata.h mythread.h mythread.cpp)

find_package(wxWidgets REQUIRED COMPONENTS net core base html xml)
find_package (SQLite3)
find_package (OpenSSL REQUIRED)

include(${wxWidgets_USE_FILE})

add_executable(myapp ${SOURCE_FILES})

#target_link_directories(myapp PRIVATE sqlite/)
target_link_libraries(myapp ${wxWidgets_LIBRARIES} database_lib ${SQLite3_LIBRARIES} OpenSSL::SSL)

