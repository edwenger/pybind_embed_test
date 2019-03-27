#include "model/SimpleBoostDecayComponent.h"

#include <cmath>
#include <stdexcept>

#include <pybind11/embed.h>

namespace py = pybind11;

SimpleBoostDecayComponent::SimpleBoostDecayComponent(std::vector<int>/*py::dict*/ params)
    : currentValue(0)
    , boostAmount(10)
    , decayRate(0.1)
{

}

void SimpleBoostDecayComponent::Update(float dt)
{
    Decay(dt);
}

void SimpleBoostDecayComponent::Notify(const std::string& event)
{
    if(event == "Boost")
    {
        Boost();
    }
    else
    {
        throw std::runtime_error("Invalid event!");
    }
}

float SimpleBoostDecayComponent::GetCurrentValue() const
{
    return currentValue;
}

void SimpleBoostDecayComponent::Decay(float dt)
{
    currentValue *= exp(-decayRate * dt);
}

void SimpleBoostDecayComponent::Boost()
{
    currentValue += boostAmount;
}
