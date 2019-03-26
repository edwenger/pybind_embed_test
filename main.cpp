#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;
using namespace py::literals;

int main() {
    py::scoped_interpreter guard{};

    py::module calc = py::module::import("config");
    py::object result = calc.attr("c2_count");
    int c2_count = result.cast<int>();

    std::cout << "c2 count: " << c2_count << std::endl;
}
