#include "renderer/resource/VertexLayout.h"

namespace te
{
    namespace vertex_layout
    {
        String getTypeStr(Type t)
        {
            switch (t)
            {
            case PNTB: return "PNTB";
            default: return "";
            }
        }

        Type getType(const String& str)
        {
            if ("PNTB" == str)
                return PNTB;
            else return Position;
        }
    }

    void VertexLayoutPredefinition::init()
    {
        // order of the vertex layout attribute
        // corresponding to the location in shader!
        vertex_layout_map[vertex_layout::Position] = {
            { "vertPos", 0, 3, 0 }
        };

        vertex_layout_map[vertex_layout::Overlay] = {
            { "vertPos", 0, 2, 0 },
            { "texCoords0", 0, 2, 8 }
        }; // Overlay is for Game GUI

        vertex_layout_map[vertex_layout::Model] = {
            { "vertPos", 0, 3, 0 },
            { "normal", 1, 3, 0 },
            { "tangent", 2, 4, 0 },
            { "joints", 3, 4, 8 },
            { "weights", 3, 4, 24 },
            { "texCoords0", 3, 2, 0 },
            { "texCoords1", 3, 2, 40 }
        };

        vertex_layout_map[vertex_layout::Partical] = {
            { "texCoords0", 0, 2, 0 },
            { "parIdx", 0, 1, 8 }
        };

        vertex_layout_map[vertex_layout::PNTB] = {
            { "vertPos", 0, 3, 0 },
            { "normal", 0, 3, 12 },
            { "tangent", 0, 3, 24 },
            { "bitangent", 0, 3, 36 }
        };

        vertex_layout_map[vertex_layout::PN] = {
            { "vertPos", 0, 3, 0 },
            { "normal", 0, 3, 12 }
        };

        vertex_layout_map[vertex_layout::PNTB_TEX] = {
            { "vertPos", 0, 3, 0 },
            { "normal", 0, 3, 12 },
            { "tangent", 0, 3, 24 },
            { "bitangent", 0, 3, 36 },
            //{ "texCoords0", 3, 2, 0 }, -- bug exists
        };
    }
    const VertexLayout & VertexLayoutPredefinition::getLayout(vertex_layout::Type vl_type)
    {
        return vertex_layout_map[vl_type];
    }
}