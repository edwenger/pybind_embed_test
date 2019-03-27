#pragma once

#include <string>
#include <vector>

#include <pybind11/embed.h>
#include "model/ModelComponent.h"

namespace py = pybind11;

class SimpleBoostDecayComponent : public ModelComponent::Registrar<SimpleBoostDecayComponent>
{
public:
    SimpleBoostDecayComponent(std::vector<int> /*py::dict*/ params);
    void Update(float dt) override;
    void Notify(const std::string& event) override;
    float GetCurrentValue() const override;

protected:
    void Decay(float dt=1.0f);
    void Boost();

protected:
    float currentValue;
    float boostAmount;
    float decayRate;
};