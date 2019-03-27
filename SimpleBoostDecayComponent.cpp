#include <cmath>
#include <stdexcept>

#include "SimpleBoostDecayComponent.h"

// SimpleBoostDecayComponent::SimpleBoostDecayComponent(
//     float boostAmount_, float decayRate_)
//     : currentValue(0)
//     , boostAmount(boostAmount_)
//     , decayRate(decayRate_)
// {
// }

// float is placeholder for py::dict
SimpleBoostDecayComponent::SimpleBoostDecayComponent(float x)
    : currentValue(x)
    , boostAmount(10)
    , decayRate(0.1)
{

}

// void SimpleBoostDecayComponent::Update(float dt)
// {
//     Decay(dt);
// }
//
// void SimpleBoostDecayComponent::Notify(const std::string& event)
// {
//     if(event == "Boost")
//     {
//         Boost();
//     }
//     else
//     {
//         throw std::runtime_error("Invalid event!");
//     }
// }

float SimpleBoostDecayComponent::GetCurrentValue() const
{
    return currentValue;
}

// void SimpleBoostDecayComponent::Decay(float dt)
// {
//     currentValue *= exp(-decayRate * dt);
// }
//
// void SimpleBoostDecayComponent::Boost()
// {
//     currentValue += boostAmount;
// }
