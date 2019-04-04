#pragma once

#include <string>
#include "ParamSet.h"

struct ModelComponent
{
    virtual ~ModelComponent() { }

    virtual void Configure(const ParamSet& pset) = 0;
    virtual void Update(float dt) = 0;
    virtual void Notify(const std::string& event) = 0;
    virtual float GetCurrentValue() const = 0;
};
