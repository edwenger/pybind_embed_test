#include <string>

#include <pybind11/pybind11.h>

#include "core/ModelComponent.h"
#include "core/ModelComponentFactory.h"
#include "model/SimpleBoostDecayComponent.h"

namespace py = pybind11;
using namespace py::literals;

class PyModelComponent : public ModelComponent {
public:
    /* Inherit the constructors */
    using ModelComponent::ModelComponent;

    /* Trampoline (need one for each virtual function) */
    void Configure(const ParamSet& pset) override {
        PYBIND11_OVERLOAD_PURE(
            void,           /* Return type */
            ModelComponent, /* Parent class */
            Configure,      /* Name of function in C++ (must match Python name) */
            pset            /* Argument(s) */
        );
    }

    void Update(float dt) override {
        PYBIND11_OVERLOAD_PURE(void, ModelComponent, Update, dt);
    }

    void Notify(const std::string& event) override {
        PYBIND11_OVERLOAD_PURE(void, ModelComponent, Notify, event);
    }

    float GetCurrentValue() const override {
        PYBIND11_OVERLOAD_PURE(float, ModelComponent, GetCurrentValue, /* no arguments */);
    }
};

PYBIND11_MODULE(dtk3, m) {

    m.def("CreateComponent", &ModelComponentFactory::CreateComponent);

    py::class_<ModelComponent, PyModelComponent> model_component(m, "ModelComponent");
    model_component
        .def(py::init<>())
        .def("Configure",
             &ModelComponent::Configure,
             "Configure the component from a ParamSet dictionary",
             "pset"_a
         )
        .def("Update",
             &ModelComponent::Update,
             "Update (i.e. Decay at decayRate) currentValue for dt",
             "dt"_a=1
         )
        .def("Notify",
             &ModelComponent::Notify,
             "Notify of an event (e.g. 'Boost')",
             "event"_a="Boost"
         )
        .def_property_readonly(
            "currentValue",
            &ModelComponent::GetCurrentValue
        );

    py::class_<SimpleBoostDecayComponent>(m, "SimpleBoostDecayComponent", model_component)
        .def(py::init<>());

}
