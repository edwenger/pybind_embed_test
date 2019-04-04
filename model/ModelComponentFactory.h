#pragma once

#include <functional>
#include <map>
#include <string>

#include <pybind11/embed.h>

#include "ModelComponent.h"

namespace py = pybind11;

class ModelComponentFactory
{
    typedef std::function<ModelComponent* ()> instantiator_function_t;
    typedef std::map<std::string, instantiator_function_t> registration_table_t;

public:
    static ModelComponent* CreateComponent(std::string name,
                                           const py::dict &params);

    static void Register(const std::string& classname,
                         instantiator_function_t _if)
    {
        GetRegistrationTable()[classname] = _if;
    }

protected:
    static registration_table_t& GetRegistrationTable()
    {
        static registration_table_t registration_table;
        return registration_table;
    }
};

#define DECLARE_FACTORY_REGISTERED(classname) \
    private: \
    class RegistrationHookCaller\
    {\
    public:\
        RegistrationHookCaller()\
        {\
            classname::in_class_registration_hook();\
        }\
    };\
    static void in_class_registration_hook()\
    {\
        ModelComponentFactory::Register(#classname, \
            []() { return (ModelComponent*)(new classname()); });\
    }\
    static RegistrationHookCaller registration_hook_caller; \

#define IMPLEMENT_FACTORY_REGISTERED(classname) \
    classname::RegistrationHookCaller classname::registration_hook_caller;
