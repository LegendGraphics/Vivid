#ifndef RENDERER_SHADEROBJECT_H
#define RENDERER_SHADEROBJECT_H

#include "base\Globals.h"

namespace te
{
    struct ShaderObject
    {
        uint32 shader_handle;

        std::vector<uint32> custom_uniform_handles;

        uint32 uni_view_mat, uni_proj_mat, uni_view_proj_mat, uni_view_proj_mat_int;
    };

    // <del>seems in Horde3D all shader resource is managed in one
    // instance of ShaderResource??? </del>
    // one kind of mesh may have one ShaderResource; light may have its
    // own ShaderResource, etc
    class ShaderResource : public RenderResource
    {
        std::vector<ShaderObject> _shaders;
    };
}

#endif
