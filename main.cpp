#include <iostream>

#include <pybind11/embed.h>

#include "model/ModelComponent.h"

namespace py = pybind11;
using namespace py::literals;

int main() {
    py::scoped_interpreter guard{};

    py::module calc = py::module::import("config");
    py::object result = calc.attr("c2_count");
    int c2_count = result.cast<int>();

    std::cout << "c2 count: " << c2_count << std::endl;

    auto mc = ModelComponent::make("SimpleBoostDecayComponent", 0.0f);
    mc->Notify("Boost");
    std::cout << "Value after Boost() = " << mc->GetCurrentValue() << std::endl;
    mc->Update(5);
    std::cout << "Value after Decay(5) = " << mc->GetCurrentValue() << std::endl;
}
