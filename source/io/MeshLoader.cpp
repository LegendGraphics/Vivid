#include "io/MeshLoader.h"
#include <sstream>
#include <fstream>
#include "common/Mesh.h"

namespace te
{
	// I need to write a file manager to read/write...

    Mesh* MeshLoader::readObjFile(const std::string& filename)
    {
		std::ifstream ifs(filename);
		std::string content((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));

        char command[256] = { 0 };
        std::stringstream in_file(content);

        if (!in_file)
            return nullptr;

        for (; ; )
        {
            in_file >> command;
            if (!in_file) break;

            if (0 == strcmp(command, "#"))
            {
                // Comment
            }
            else if (0 == strcmp(command, "v"))
            {
                // Vertex Position
                float x, y, z;
                in_file >> x >> y >> z;
                _positions.push_back(Vector3(x, y, z));
            }
            else if (0 == strcmp(command, "vt"))
            {
                // Vertex TexCoord
                float u, v;
                in_file >> u >> v;
                _uvs.push_back(Vector2(u, v));
            }
            else if (0 == strcmp(command, "vn"))
            {
                // Vertex Normal
                float x, y, z;
                in_file >> x >> y >> z;
                _normals.push_back(Vector3(x, y, z));
            }
            else if (0 == strcmp(command, "f"))
            {
                // Face
                int i_position, i_texcoord, i_normal;
                ObjFace face;
                memset(&face, 0, sizeof(face));

                for (int i_face = 0; i_face < 3; i_face ++)
                {
                    // OBJ format uses 1-based arrays
                    in_file >> i_position;
                    face.pos_idx[i_face] = i_position - 1;

                    if ('/' == in_file.peek())
                    {
                        in_file.ignore();

                        if ('/' != in_file.peek())
                        {
                            // Optional texture coordinate
                            in_file >> i_texcoord;
                            face.tex_idx[i_face] = i_texcoord - 1;
                        }

                        if ('/' == in_file.peek())
                        {
                            in_file.ignore();

                            // Optional vertex normal
                            in_file >> i_normal;
                            face.nrm_idx[i_face] = i_normal - 1;
                        }
                    }
                }

                _triangles.push_back(face);
            }
            else if (0 == strcmp(command, "usemtl"))
            {
                if (!_subsets.empty())
                {
                    _subsets.back().index_count = _triangles.size() * 3 - _subsets.back().index_start;
                }

                MeshSubset subset;
                in_file >> subset.mtl_name;
                subset.index_start = _triangles.size() * 3;

                _subsets.push_back(subset);
            }
            else
            {
                // Unimplemented or unrecognized command
            }

            in_file.ignore(1000, '\n');
        }

        if (!_subsets.empty())
        {
            _subsets.back().index_count = _triangles.size() * 3 - _subsets.back().index_start;
        }
        else
        {
            // not sub mtl used
            MeshSubset subset;
            subset.mtl_name = "undefined";
            subset.index_start = 0;
            subset.index_count = _triangles.size() * 3;
            _subsets.push_back(subset);
        }

        return createObjMesh();
    }

    Mesh* MeshLoader::createObjMesh()
    {
        Mesh* mesh = new Mesh();

        std::vector<Vertex> vertices;
        std::vector<int>    indices;
		std::vector<VertexIndices> ver_indices;

        for (int i = 0; i < _triangles.size(); ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                Vertex vertex;
				VertexIndices ver_idx;
                int pos_idx = _triangles[i].pos_idx[j];
                int tex_idx = _triangles[i].tex_idx[j];
                int nrm_idx = _triangles[i].nrm_idx[j];

                vertex.position = _positions[pos_idx];
				ver_idx.pos_idx = pos_idx;
				if (!_uvs.empty())
				{
					vertex.texcoord = _uvs[tex_idx];
					ver_idx.tex_idx = tex_idx;
				}
				if (!_normals.empty())
				{
					vertex.normal = _normals[nrm_idx];
					ver_idx.nrm_idx = nrm_idx;
				}	

                int index = addVertex(&vertex, &ver_idx, vertices, ver_indices);
                indices.push_back(index);
            }
        }

        mesh->setVertexArray(vertices);
        mesh->setTriangleArray(indices);

        return mesh;

        //// create vb and ib
        //VertexBuffer* cached_vb = new VertexBuffer(sizeof(Vertex), vertices.size());
        //IndexBuffer* cached_ib = new IndexBuffer(indices.size());

        //memcpy(cached_vb->data, &(vertices[0]), sizeof(Vertex) * vertices.size());
        //memcpy(cached_ib->data, &(indices[0]), sizeof(int) * indices.size());
    }

    int MeshLoader::addVertex(Vertex* vertex, VertexIndices* ver_idx, std::vector<Vertex>& vertices, std::vector<VertexIndices>& ver_indices)
    {
		// check whether has the same vertex indices
		bool has_same = false;
		for (int i = 0, i_end = ver_indices.size(); i < i_end; ++ i)
		{
			if (ver_indices[i].pos_idx == ver_idx->pos_idx &&
				ver_indices[i].tex_idx == ver_idx->tex_idx &&
				ver_indices[i].nrm_idx == ver_idx->nrm_idx)
			{
				has_same = true;
				return i;
			}
		}
		
		if (!has_same)
		{
			int index = vertices.size();
			vertices.push_back(*vertex);
			ver_indices.push_back(*ver_idx);
			return index;
		}
    }
}