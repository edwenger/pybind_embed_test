#include <core/ModelComponentFactory.h>

#include <exception>

namespace core {
ModelComponent*
ModelComponentFactory::CreateComponent(std::string name, const ParamSet& pset)
{
  registration_table_t::iterator it;
  it = GetRegistrationTable().find(name);

  if (it != GetRegistrationTable().end())
  {
      ModelComponent* obj = (it->second)();
      obj->Configure(pset);
      return obj;
  }
  else
  {
      throw std::invalid_argument("Invalid class!");
  }
}
}
