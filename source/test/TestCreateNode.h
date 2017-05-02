
#include "base/Director.h"
#include "common/Scene.h"
#include "common/Node.h"
#include "common/MeshFilter.h"
#include "base/Singleton.hpp"
#include "io/ResourceLoader.h"
using namespace te;

int main(int argc, char** argv)
{ 
    Director::getInstance()->initialize();
    // create a scene
    Scene* scene = new Scene;
    // add a mesh filter to scene root node
    //Mesh* m = new Mesh;
    //ResourceLoader::load(m, "cube_emptyTags.mesh");
    /*scene->getSceneRoot()->addComponent<MeshFilter>();
    scene->getSceneRoot()->getComponent<MeshFilter>()->load("cube_emptyTags.mesh");

    Scene* scene2 = new Scene;
    scene2->getSceneRoot()->addComponent<MeshFilter>();
    scene2->getSceneRoot()->getComponent<MeshFilter>()->load("cube_emptyTags.mesh");*/

    Node* node = Node::create("cube.node.xml");
    Node* node1 = Node::create("cube1.node.xml");

    NodeTree* node_tree = new NodeTree(node);
    node_tree->addChildTree(new NodeTree(node1));
    scene->setSceneRoot(node_tree);

    Director::getInstance()->setActiveScene(scene);
    Director::getInstance()->start();

    return 0;
}

