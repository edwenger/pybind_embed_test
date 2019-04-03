#include "SimpleBoostDecayComponent.h"

#include <cmath>
#include <stdexcept>

#include <pybind11/embed.h>

namespace py = pybind11;

SimpleBoostDecayComponent::SimpleBoostDecayComponent(const py::dict &params)
    : currentValue(0)
    , boostAmount(params["boostAmount"].cast<float>())
    , decayRate(params["decayRate"].cast<float>())
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
