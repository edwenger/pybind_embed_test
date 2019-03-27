#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <cxxabi.h>

/*
Cargo-culted CRTP version of factory pattern from:
http://www.nirfriedman.com/2018/04/29/unforgettable-factory
*/

std::string demangle(const char *name) {

  int status = -4; // some arbitrary value to eliminate the compiler warning

  std::unique_ptr<char, void (*)(void *)> res{
      abi::__cxa_demangle(name, NULL, NULL, &status), std::free};

  return (status == 0) ? res.get() : name;
}

template <class Base, class... Args> class Factory {
public:

  template <class ... T>
  static std::unique_ptr<Base> make(const std::string &s, T&&... args) {
      return data().at(s)(std::forward<T>(args)...);
  }

  template <class T> struct Registrar : Base {
    friend T;

    static bool registerT() {
      const auto name = demangle(typeid(T).name());
      Factory::data()[name] = [](Args... args) -> std::unique_ptr<Base> {
        return std::make_unique<T>(std::forward<Args>(args)...);
      };
      return true;
    }
    static bool registered;

  private:
    Registrar() : Base(Key{}) { (void)registered; }
  };

  friend Base;

private:
  class Key {
    Key(){};
    template <class T> friend struct Registrar;
  };
  using FuncType = std::unique_ptr<Base> (*)(Args...);
  Factory() = default;
  virtual ~Factory() = default; // added to resolve compiler warnings

  static auto &data() {
    static std::unordered_map<std::string, FuncType> s;
    return s;
  }
};

template <class Base, class... Args>
template <class T>
bool Factory<Base, Args...>::Registrar<T>::registered =
    Factory<Base, Args...>::Registrar<T>::registerT();
