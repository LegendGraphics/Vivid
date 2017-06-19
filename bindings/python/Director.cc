
py::class_<vivid::Director> Director(m, "Director");


Director
.def(py::init<>())
.def("initialize", &vivid::Director::initialize)
.def("start", &vivid::Director::start);
//.def("setActiveScene", &vivid::Director::setActiveScene);

