add_library(model STATIC ModelComponent.cpp SimpleBoostDecayComponent.cpp)

# include top-level directory to allow full include paths
target_include_directories(model PUBLIC ${CMAKE_SOURCE_DIR})

# link library against pybind11
target_link_libraries(model PRIVATE pybind11::embed)
