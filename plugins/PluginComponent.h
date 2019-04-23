#pragma once

#include <string>

#include <core/ModelComponent.h>


class PluginComponent : public ModelComponent
{

public:
    PluginComponent();

    void Configure(const ParamSet& pset) override;
    void Update(float dt=1.0f) override;
    void Notify(const std::string& event) override;
    float GetCurrentValue() const override;

protected:
    float currentValue;
};
