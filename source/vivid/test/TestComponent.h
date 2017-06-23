
#include "base/Director.h"
#include "common/Scene.h"
#include "common/Node.h"
#include "common/MeshRender.h"
#include "common/Camera.h"
#include "common/SpaceState.h"
#include "base/Singleton.hpp"
#include "io/ResourceLoader.h"
using namespace vivid;

int main(int argc, char** argv)
{ 
    if (argc < 2)
    {
        std::cout << "please add data path.\n";
        //return 1;
    }
    else
    {
        ResourceLoader::setDataPath(String(argv[1]));
    }

 
    Node* node = new Node;
    //Node* node1 = Node::create("cube1.node.xml");
    node->addComponent<MeshRender>();
    //node->addComponent<MeshRender>();

    //node->addComponent<MeshRender>();


    node->addComponent<CameraState>();

    //node->addComponent<SpaceState>();
    node->addComponent<SpaceState>();

    return 0;
}

