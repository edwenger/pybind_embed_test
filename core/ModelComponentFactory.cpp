#include "ModelComponentFactory.h"

#include <exception>


ModelComponent*
ModelComponentFactory::CreateComponent(std::string name, const ParamSet& ps)
{
  registration_table_t::iterator it;
  it = GetRegistrationTable().find(name);

  if (it != GetRegistrationTable().end())
  {
      ModelComponent* obj = (it->second)();
      obj->Configure(ps);
      return obj;
  }
  else
  {
      throw std::invalid_argument("Invalid class!");
  }
}
