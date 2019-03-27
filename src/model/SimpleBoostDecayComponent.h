#pragma once

#include "IModelComponent.h"

class SimpleBoostDecayComponent : IModelComponent
{
public:
    SimpleBoostDecayComponent(float boostAmount_, float decayRate_);
    void Update(float dt) override;
    void Notify(const std::string& event) override;
    float GetCurrentValue() const;

protected:
    void Decay(float dt=1.0f);
    void Boost();

protected:
    float currentValue;
    float boostAmount;
    float decayRate;
};
