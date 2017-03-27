
#include "base/Director.h"
#include "common/Scene.h"
#include "common/MeshFilter.h"
#include "base/Singleton.hpp"
#include "io/ResourceLoader.h"
using namespace te;

int main(int argc, char** argv)
{ 
    // create a scene
    Scene* scene = new Scene;
    // add a mesh filter to scene root node
    Mesh* m = new Mesh;
    ResourceLoader::load(m, "cube_emptyTags.mesh");
    scene->getSceneRoot()->addComponent<MeshFilter>(m);
    Director::getInstance()->setActiveScene(scene);
    Director::getInstance()->start();

    return 0;
}

