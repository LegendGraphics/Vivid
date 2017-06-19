#include "pybind11/pybind11.h"

#include "vivid/base/Timer.h"
#include "vivid/base/Director.h"

namespace py = pybind11;

py::module m("PyVivid", "Vivid python module");

PYBIND11_PLUGIN(PyVivid) {

#include "Timer.cc"
#include "Director.cc"

    return m.ptr();
}