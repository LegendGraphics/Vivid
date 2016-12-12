#ifndef IO_MESH_LOADER_H
#define IO_MESH_LOADER_H

namespace te
{
    class MeshLoader
    {
    public:
        static Mesh* readObjFile(const std::string& filename);
    };
}


#endif // IO_MESH_LOADER_H