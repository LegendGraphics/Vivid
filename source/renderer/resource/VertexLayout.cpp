#include "VertexLayout.h"

namespace te
{
    void VertexLayoutPredefinition::init()
    {
        // order of the vertex layout attribute
        // corresponding to the location in shader!
        vertexLayoutMap[vertex_layout::Position] = {
            { "vertPos", 0, 3, 0 }
        };

        vertexLayoutMap[vertex_layout::Overlay] = {
            { "vertPos", 0, 2, 0 },
            { "texCoords0", 0, 2, 8 }
        }; // Overlay is for Game GUI

        vertexLayoutMap[vertex_layout::Model] = {
            { "vertPos", 0, 3, 0 },
            { "normal", 1, 3, 0 },
            { "tangent", 2, 4, 0 },
            { "joints", 3, 4, 8 },
            { "weights", 3, 4, 24 },
            { "texCoords0", 3, 2, 0 },
            { "texCoords1", 3, 2, 40 }
        };

        vertexLayoutMap[vertex_layout::Partical] = {
            { "texCoords0", 0, 2, 0 },
            { "parIdx", 0, 1, 8 }
        };

        vertexLayoutMap[vertex_layout::PNTB] = {
            { "vertPos", 0, 3, 0 },
            { "normal", 0, 3, 12 },
            { "tangent", 0, 3, 24 },
            { "bitangent", 0, 3, 36 }
        };
    }
    const VertexLayout & VertexLayoutPredefinition::getLayout(vertex_layout::Type vlType)
    {
        return vertexLayoutMap[vlType];
    }
}