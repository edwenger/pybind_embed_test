#include <string>

#include <pybind11/pybind11.h>

#include "core/ModelComponentFactory.h"
#include "model/SimpleBoostDecayComponent.h"

namespace py = pybind11;
using namespace py::literals;

PYBIND11_MODULE(dtk3, m) {

    m.def("ModelComponent", &ModelComponentFactory::CreateComponent);

    py::class_<SimpleBoostDecayComponent>(m, "SimpleBoostDecayComponent")
            .def(py::init<>())
            .def("Configure",
                 &SimpleBoostDecayComponent::Configure,
                 "Configure the component from a ParamSet dictionary",
                 "pset"_a
             )
            .def("Update",
                 &SimpleBoostDecayComponent::Update,
                 "Update (i.e. Decay at decayRate) currentValue for dt",
                 "dt"_a=1
             )
            .def("Notify",
                 &SimpleBoostDecayComponent::Notify,
                 "Notify of an event (e.g. 'Boost')",
                 "event"_a="Boost"
             )
            .def_property_readonly(
                "currentValue",
                &SimpleBoostDecayComponent::GetCurrentValue
            )
            .def("__repr__",
                [](const SimpleBoostDecayComponent &c) {
                    std::string s = std::to_string(c.GetCurrentValue());
                    return "<dtk3.SimpleBoostDecayComponent with currentValue of " + s + ">";
                }
            );
}
