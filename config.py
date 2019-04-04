""" Our main.cpp will read this module using pybind11 for embedding """


model_name = "SimpleBoostDecayComponent"

model_params = dict(
    boostAmount=200,
    decayRate=0.2
)


plugin_dylib = "build/plugins/libplugin.dylib"

plugin_name = "PluginComponent"

plugin_params = dict()
