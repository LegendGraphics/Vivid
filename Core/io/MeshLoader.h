#ifndef IO_MESH_LOADER_H
#define IO_MESH_LOADER_H

namespace te
{
    class MeshLoader
    {
    public:
        struct ObjFace
        {
            int pos_idx[3];
            int nrm_idx[3];
            int tex_idx[3];
            int tgt_idx[3];
        };

        struct Subset
        {
            std::string mtl_name;
            int start_idx;
            int end_idx;
        };

        Mesh* readObjFile(const std::string& filename);

    protected:
        Mesh* createObjMesh();
        int addVertex(Vertex* vertex, std::vector<Vertex>& vertices);

    protected:
        Vec3Array _positions;
        Vec3Array _normals;
        Vec3Array _colors;
        Vec2Array _uvs;
        Vec4Array _tangents;
        std::vector<ObjFace> _triangles;
        MeshSubsets _subsets;

    };
}


#endif // IO_MESH_LOADER_H