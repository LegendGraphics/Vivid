
py::class_<vivid::Director> Director(m, "Director");


Director
.def(py::init<>())
.def_static("instance", &vivid::Director::getInstance)
.def("initialize", &vivid::Director::initialize)
.def("start", &vivid::Director::start)
.def("setActiveScene", &vivid::Director::setActiveScene);

