cmake_minimum_required(VERSION 3.0)
project(emodRun)

add_subdirectory(pybind11)

enable_testing()
add_subdirectory(tests)

add_executable(emodRun main.cpp)
target_link_libraries(emodRun PRIVATE pybind11::embed)
