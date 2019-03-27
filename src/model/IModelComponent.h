#pragma once

#include <string>

struct IModelComponent
{
    virtual void Update(float dt) = 0;
    virtual void Notify(const std::string& event) = 0;
};
