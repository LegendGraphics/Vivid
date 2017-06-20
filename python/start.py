import PyVivid

def start():
	director = PyVivid.Director.instance()
	director.initialize()

	scene = PyVivid.Scene()

	node = PyVivid.Node.create("duck.node.xml")
	node_tree = PyVivid.NodeTree(node)

	scene.setSceneRoot(node_tree)

	director.setActiveScene(scene)
	director.start()

if __name__ == '__main__':
	start()