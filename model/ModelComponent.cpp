#include "ModelComponent.h"

#include <exception>

#include "SimpleBoostDecayComponent.h"

ModelComponent* ModelComponent::make(std::string name, const py::dict &params)
{
  if (name == "SimpleBoostDecayComponent")
    return new SimpleBoostDecayComponent(params);
  else
    throw std::invalid_argument("Invalid class!");
}
