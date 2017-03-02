
#include "base/Director.h"
#include "common/Scene.h"

using namespace te;




int main(int argc, char** argv)
{ 
    Scene* scene = new Scene;
    Director::getInstance()->setActiveScene(scene);
    Director::getInstance()->start();

    return 0;
}

