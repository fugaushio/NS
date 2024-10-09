cmake_minimum_required(VERSION 3.28)

option(enable_OPENMP "Enable OpenMP" ON)
option(enable_GLOG "Enable GLOG" OFF)

set(CMAKE_BUILD_RPATH "/opt/intel/oneapi/compiler/2024.2/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


#-----compiler options
if(NOT DEFINED compiler)
  set(base_compile_options "-Wall -Wextra -O3")
  if(enable_OPENMP)
    set(base_compile_options ${base_compile_options} " -fopenmp")
   endif()
endif()

if(compiler STREQUAL intel)
  set(CMAKE_C_COMPILER "/opt/intel/oneapi/compiler/2024.2/bin/icx")
  set(CMAKE_CXX_COMPILER "/opt/intel/oneapi/compiler/2024.2/bin/icpx")
  set(base_compile_options "-Wall -Wextra -O3")
  if(enable_OPENMP)
    set(base_compile_options ${base_compile_options} " -qopenmp")
  endif()
elseif(DEFINED compiler)
  message(FATAL ERROR "invalid compiler")
endif()

set (PROJECT_NAME Test)

project(${PROJECT_NAME} CXX)

add_subdirectory(src)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} lib)

# Google-glog
if(enable_GLOG)
  set(GLOG_DIR ${GLOG_DIR} CACHE PATH "...")
  find_package(GLOG REQUIRED)
  include_directories(${GLOG_INCLUDE_DIR})
  message( STATUS "GLOG include dir  : "      ${GLOG_INCLUDE_DIR})
  MESSAGE("find GLOG")
endif()
