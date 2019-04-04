#pragma once

#include <string>

#include "ParamSet.h"


class ModelComponent
{
    
public:
    virtual void Configure(const ParamSet& ps) = 0;
    virtual void Update(float dt) = 0;
    virtual void Notify(const std::string& event) = 0;
    virtual float GetCurrentValue() const = 0;
};
