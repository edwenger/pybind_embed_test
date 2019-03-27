#pragma once

#include <string>

#include "ModelComponent.h"

class SimpleBoostDecayComponent : public ModelComponent::Registrar<SimpleBoostDecayComponent>
{
public:
    // SimpleBoostDecayComponent(float boostAmount_, float decayRate_);
    SimpleBoostDecayComponent(float x) : currentValue(x) {} // float is placeholder for py::dict
//     void Update(float dt) override;
//     void Notify(const std::string& event) override;
    float GetCurrentValue() const override { return currentValue; }

// protected:
//     void Decay(float dt=1.0f);
//     void Boost();

protected:
    float currentValue;
    // float boostAmount;
    // float decayRate;
};
