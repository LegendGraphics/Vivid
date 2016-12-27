#include "common/MeshFilter.h"

namespace te
{
	MeshFilter::MeshFilter(Mesh* mesh)
		:_mesh(mesh)
	{

	}

	void MeshFilter::setMesh(Mesh* mesh)
	{
		_mesh = mesh;
	}
}

