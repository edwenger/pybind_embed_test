#pragma once

#include <string>
#include <vector>

#include <pybind11/embed.h>

namespace py = pybind11;

class ModelComponent
{
public:
    static ModelComponent* make(std::string name, const py::dict &params);

    virtual void Update(float dt) = 0;
    virtual void Notify(const std::string& event) = 0;
    virtual float GetCurrentValue() const = 0;
};
