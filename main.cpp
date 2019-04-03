#include <exception>
#include <iostream>
#include <string>

#include <pybind11/embed.h>
#include "model/ModelComponent.h"

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

    py::module calc = py::module::import(module_name.c_str());
    auto params = calc.attr("model_params");

    auto mc = ModelComponent::make("SimpleBoostDecayComponent", params);
    mc->Notify("Boost");
    std::cout << "Value after Boost() = " << mc->GetCurrentValue() << std::endl;
    mc->Update(5);
    std::cout << "Value after Decay(5) = " << mc->GetCurrentValue() << std::endl;
}
