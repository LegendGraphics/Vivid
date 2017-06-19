
py::class_<vivid::Timer> Timer(m, "Timer");


Timer
.def(py::init<>())
.def("setEnabled", &vivid::Timer::setEnabled)
.def("reset", &vivid::Timer::reset)
.def("getElapsedTime", &vivid::Timer::getElapsedTime);

