#include <iostream>
#include <pybind11/embed.h>
#include "src/model/SimpleBoostDecayComponent.h"

namespace py = pybind11;
using namespace py::literals;

int main() {
    py::scoped_interpreter guard{};

    py::module calc = py::module::import("config");
    py::object result = calc.attr("c2_count");
    int c2_count = result.cast<int>();

    std::cout << "c2 count: " << c2_count << std::endl;

    SimpleBoostDecayComponent *mc = new SimpleBoostDecayComponent(10, 0.1);
    mc->Notify("Boost");
    std::cout << "Value after Boost() = " << mc->GetCurrentValue() << std::endl;
    mc->Update(5);
    std::cout << "Value after Decay(5) = " << mc->GetCurrentValue() << std::endl;
}
