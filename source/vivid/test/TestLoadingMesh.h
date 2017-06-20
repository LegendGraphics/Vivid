#include <iostream>
#include <memory>
#include "common/Mesh.h"
#include "common/MeshFilter.h"


using namespace te;

int main(int argc, char** argv)
{
    MeshRes mr;
    mr.load("cube_emptyTags.mesh");

    Mesh* m = new Mesh;
    m->init(&mr);

    getchar();
    return 0;
}
