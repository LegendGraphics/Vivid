#include "pybind11/pybind11.h"

#include "vivid/base/Timer.h"
#include "vivid/base/Director.h"
#include "vivid/common/Scene.h"
#include "vivid/common/Node.h"

namespace py = pybind11;

py::module m("PyVivid", "Vivid python module");

PYBIND11_PLUGIN(PyVivid) {

#include "py_vivid/py_Timer.cc"
#include "py_vivid/py_Scene.cc"
#include "py_vivid/py_Director.cc"
#include "py_vivid/py_NodeTree.cc"
#include "py_vivid/py_Node.cc"

    return m.ptr();
}