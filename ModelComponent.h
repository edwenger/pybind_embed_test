#pragma once

#include <string>

#include "Factory.h"

struct ModelComponent : Factory<ModelComponent, float> // float is placeholder for py::dict
{
    ModelComponent(Key) {}

    // virtual void Update(float dt) = 0;
    // virtual void Notify(const std::string& event) = 0;
    virtual float GetCurrentValue() const = 0;
};
