cmake_minimum_required(VERSION 3.28.3 FATAL_ERROR)
project(xwsclient
        VERSION "0.0.1"
        DESCRIPTION "An asynchronous websocket client for market providers!"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

message(STATUS "CMAKE_BULD_TYPE: " ${CMAKE_BUILD_TYPE})

find_package(Boost 1.66.0 REQUIRED COMPONENTS system)
find_package(glog CONFIG REQUIRED)
find_package(gflags CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_library(cxx_setup INTERFACE)
target_include_directories(cxx_setup INTERFACE ${PROJECT_SOURCE_DIR})
target_link_libraries(cxx_setup INTERFACE
                                ${Boost_LIBRARIES}
                                glog::glog
                                gflags::gflags
                                nlohmann_json::nlohmann_json)

add_subdirectory(${PROJECT_NAME})
add_subdirectory(executables)

target_compile_features(cxx_setup INTERFACE cxx_std_17)
target_compile_options(cxx_setup INTERFACE -Weffc++)