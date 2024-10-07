cmake_minimum_required(VERSION 3.28)

set (PROJECT_NAME Test)

project(${PROJECT_NAME} CXX)
set (LIBRARY_DIR "/root/c++/NS/src")
add_library(lib STATIC ${LIBRARY_DIR}/calc.cpp)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} lib)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBRARY_DIR})
