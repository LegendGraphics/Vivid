
#include "base/Director.h"
#include "common/Scene.h"
#include "common/MeshFilter.h"
#include "base/Singleton.hpp"
using namespace te;

int main(int argc, char** argv)
{ 
    // create a scene
    Scene* scene = new Scene;
    // add a mesh filter to scene root node
    MeshRes mr;
    mr.load("cube_emptyTags.mesh");
    Mesh* m = new Mesh;
    m->init(&mr);
    scene->getSceneRoot()->addComponent<MeshFilter>(m);
    DirectorS::getInstance()->setActiveScene(scene);
    DirectorS::getInstance()->start();

    return 0;
}

