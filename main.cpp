#include <exception>
#include <iostream>
#include <string>

#include <dlfcn.h>
#include <pybind11/embed.h>
#include "core/ModelComponentFactory.h"

namespace py = pybind11;

int main(int argc, char** argv) {

    if (argc != 2)
    {
        throw std::invalid_argument(
            "\nOne and only one argument! Usage: 'emodRun config.py'");
    }

    std::string config_file = argv[1];
    if (config_file.substr(config_file.size() - 3, 3) != ".py")
    {
        throw std::invalid_argument(
            "\nArgument should have .py extension! Usage: 'emodRun config.py'");
    }

    std::string module_name = config_file.substr(0, config_file.size()-3);

    py::scoped_interpreter guard{};

    py::module cfg = py::module::import(module_name.c_str());
    auto model_name = cfg.attr("model_name").cast<std::string>();
    auto model_params = cfg.attr("model_params");

    std::cout << "Creating " << model_name.c_str() << " component..." << std::endl;
    auto mc = ModelComponentFactory::CreateComponent(model_name, model_params);
    mc->Notify("Boost");
    std::cout << "  Value after Boost() = " << mc->GetCurrentValue() << std::endl;
    mc->Update(5);
    std::cout << "  Value after Decay(5) = " << mc->GetCurrentValue() << std::endl;

    /*** Loading plugin ***/

    auto plugin_dylib = cfg.attr("plugin_dylib").cast<std::string>();

    void *libplugin = dlopen(plugin_dylib.c_str(), RTLD_LAZY);
    if (!libplugin) {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    // reset errors
    dlerror();

    factory_register_t* factory_register = (factory_register_t*) dlsym(libplugin, "factory_register");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
        return 1;
    }

    factory_register();

    auto plugin_name = cfg.attr("plugin_name").cast<std::string>();
    auto plugin_params = cfg.attr("plugin_params");

    std::cout << "Creating " << plugin_name.c_str() << " component..." << std::endl;
    auto mc2 = ModelComponentFactory::CreateComponent(plugin_name, plugin_params);
    for (int i = 0; i < 4; i++)
    {
        mc2->Update(i);
        std::cout << mc2->GetCurrentValue() << "...";
    }
    std::cout << "Who do we appreciate? pybind11!" << std::endl;
}
