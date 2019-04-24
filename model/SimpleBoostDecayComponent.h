#pragma once

#include <string>

#include <core/ModelComponent.h>
#include <core/ModelComponentFactory.h>


namespace dtk {
namespace model {

class SimpleBoostDecayComponent : public ModelComponent
{

    DECLARE_FACTORY_REGISTERED(SimpleBoostDecayComponent)

public:
    SimpleBoostDecayComponent();

    void Configure(const ParamSet& pset) override;
    void Update(float dt=1.0f) override;
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

}  // dtk::model namespace
}  // dtk namespace
