A test project using pybind11 to explore modularity, extensibility, and configurability.

* Embed the Python interpreter for simpler configuration of executable and tests
* Export Python bindings to C++ classes and factory methods for easy testing

Building libraries, executable, and python module according to top-level CMakeLists.txt:

```
cmake -H. -Bbuild -GNinja
cd build
ninja
```

Running executable:

```
./build/emodRun config.py
```

Testing exported Python objects (test/test_bindings.py):

```
import dtk3

mc = dtk3.ModelComponent("SimpleBoostDecayComponent", dict(bboostAmount=2.7, decayRate=0.2))
mc.Notify("Boost")
mc.Update(dt=5.0)

mc = dtk3.SimpleBoostDecayComponent()
mc.Configure(dict(boostAmount=2, decayRate=0))
mc.Notify("Boost")
```
