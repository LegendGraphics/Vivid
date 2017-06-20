
py::class_<vivid::Node> Node(m, "Node");


Node
.def_static("create", &vivid::Node::create);

