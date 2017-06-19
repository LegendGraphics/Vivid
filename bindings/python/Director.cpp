//#include "pybind11/pybind11.h"
//#include "vivid/base/Director.h"
//
//namespace py = pybind11;
//
//
//PYBIND11_PLUGIN(PyVivid) {
//    py::module m("PyVivid", "Vivid python module");
//
//    py::class_<vivid::Director>(m, "Director");
//        /*.def(py::init<>())
//        .def("setEnabled", &vivid::Timer::setEnabled)
//        .def("reset", &vivid::Timer::reset)
//        .def("getElapsedTime", &vivid::Timer::getElapsedTime);*/
//
//    return m.ptr();
//}