add_library(plugin SHARED PluginComponent.cpp)

# include top-level directory to allow full include paths
target_include_directories(plugin PUBLIC ${CMAKE_SOURCE_DIR})

# link library against pybind11
target_link_libraries(plugin PRIVATE pybind11::embed core)
