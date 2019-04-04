add_library(core STATIC ModelComponentFactory.cpp)

# include top-level directory to allow full include paths
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR})

# link library against pybind11
target_link_libraries(core PRIVATE pybind11::embed)
