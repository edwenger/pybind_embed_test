#include <model/SimpleBoostDecayComponent.h>

#include <cmath>
#include <stdexcept>


namespace dtk {
namespace model {

IMPLEMENT_FACTORY_REGISTERED(SimpleBoostDecayComponent)


SimpleBoostDecayComponent::SimpleBoostDecayComponent()
    : currentValue(0)
    , boostAmount(0)
    , decayRate(0)
{

}

void SimpleBoostDecayComponent::Configure(const ParamSet& pset)
{
    boostAmount = pset["boostAmount"].cast<float>();
    decayRate = pset["decayRate"].cast<float>();
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

}  // dtk::model namespace
}  // dtk namespace
