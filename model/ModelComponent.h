#pragma once

#include <string>
#include <vector>

#include <pybind11/embed.h>
#include "core/Factory.h"

namespace py = pybind11;

struct ModelComponent : Factory<ModelComponent, std::vector<int> /*py::dict*/>
{
    ModelComponent(Key) {}

    virtual void Update(float dt) = 0;
    virtual void Notify(const std::string& event) = 0;
    virtual float GetCurrentValue() const = 0;
};
