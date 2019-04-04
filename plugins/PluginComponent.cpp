#include "PluginComponent.h"

#include "core/ModelComponentFactory.h"


PluginComponent::PluginComponent()
    : currentValue(0)
{
}

void PluginComponent::Configure(const ParamSet& pset)
{
}

void PluginComponent::Update(float dt)
{
    currentValue += 2;
}

void PluginComponent::Notify(const std::string& event)
{
}

float PluginComponent::GetCurrentValue() const
{
    return currentValue;
}

extern "C" void factory_register()
{
    ModelComponentFactory::Register(
        "PluginComponent",
        []()
        {
            return (ModelComponent*)(new PluginComponent());
        }
    );
}
