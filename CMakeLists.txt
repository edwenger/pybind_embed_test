# A useful example can be found here:
# https://cliutils.gitlab.io/modern-cmake/chapters/basics/example.html

cmake_minimum_required(VERSION 3.0)
project(dtk3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(pybind11)

add_subdirectory(core)

add_subdirectory(model)

add_subdirectory(plugins)

add_executable(emodRun main.cpp)
target_link_libraries(emodRun PRIVATE pybind11::embed core model)

pybind11_add_module(dtk3 modules.cpp)
target_include_directories(dtk3 PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(dtk3 PRIVATE pybind11::embed core model)
