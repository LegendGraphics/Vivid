
py::class_<vivid::Scene> Scene(m, "Scene");


Scene
.def(py::init<>())
.def("setSceneRoot", &vivid::Scene::setSceneRoot);

