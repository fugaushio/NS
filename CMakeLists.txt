cmake_minimum_required(VERSION 3.28)

set (PROJECT_NAME Test)

project(${PROJECT_NAME} CXX)
#set (LIBRARY_DIR "/home/ushio/c++/NS/src")
#set (DATA_DIR "/home/ushio/c++/NS/data")
add_subdirectory(src)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} lib)
#add_library(lib SHARED namelist.cpp)
#add_executable(${PROJECT_NAME} main.cpp)
#target_link_libraries(${PROJECT_NAME} PUBLIC lib)
#target_include_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_DIR} ${DATA_DIR})
