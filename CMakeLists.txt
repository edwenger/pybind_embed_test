# A useful example can be found here:
# https://cliutils.gitlab.io/modern-cmake/chapters/basics/example.html

cmake_minimum_required(VERSION 3.0)
project(emodRun VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(pybind11)

enable_testing()
add_subdirectory(tests)

add_library(model SHARED model/SimpleBoostDecayComponent.cpp)

add_executable(emodRun main.cpp)
target_link_libraries(emodRun PRIVATE pybind11::embed model)
