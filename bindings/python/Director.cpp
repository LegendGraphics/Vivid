#include "pybind11/pybind11.h"
#include "vivid/base/Timer.h"

namespace py = pybind11;

struct Pet {
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }

    std::string name;
};


PYBIND11_PLUGIN(example1) {
    py::module m("example1", "pybind11 example plugin");

    py::class_<Pet>(m, "Pet")
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName);

    return m.ptr();
}


//PYBIND11_PLUGIN(example) {
//    py::module m("example", "pybind11 example plugin");
//
//    py::class_<te::Timer>(m, "Timer")
//        .def("setEnabled", &te::Timer::setEnabled)
//        .def("reset", &te::Timer::reset)
//        .def("getElapsedTime", &te::Timer::getElapsedTime);
//
//    return m.ptr();
//}