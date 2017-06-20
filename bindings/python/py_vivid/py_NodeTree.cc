
py::class_<vivid::NodeTree> NodeTree(m, "NodeTree");


NodeTree
.def(py::init<vivid::Node*>())
.def("setSceneRoot", &vivid::Scene::setSceneRoot);

