#ifndef RENDERER_RESOURCE_STREAM_H
#define RENDERER_RESOURCE_STREAM_H

#include "common/Shader.h"

namespace te
{
    namespace vertex_layout
    {
        struct IndexStream
        {
            uint32 size; // size in bytes
            void* raw_data;
            GPUHandle* res;
        };

        struct VertexStream
        {
            uint32 stride; // number of component for each element in a vertex array, in bytes
                           // for example an array for position has element {XYZ} and its stride is 3
            uint32 size; // size in bytes
            void* raw_data;
            GPUHandle* res;
        };

        struct VertexDeclarationStream
        {
            vertex_layout::Type layout_type;
            std::vector<GPUHandle*> vertex_buffers; // notice: vertex_buffers might be duplicated here
                                                    // because multiple attributes may share one vertex buffer
            GPUHandle*              index_buffer;
            GPUHandle*              res;
        };
    }

    namespace shader_data
    {
        enum Class {
            SCALAR = 0,
            VECTOR2,
            VECTOR3,
            VECTOR4,
            MATRIX4X4,
            UINT,
            INT,
            BOOL,

            SCALAR_ARRAY,
            VECTOR2_ARRAY,
            VECTOR3_ARRAY,
            VECTOR4_ARRAY,
            MATRIX4X4_ARRAY,
            UINT_ARRAY,
            INT_ARRAY,
            BOOL_ARRAY,

            UNKNOWN_CLASS,
            NUM_CLASSES = UNKNOWN_CLASS
        };

        struct ShaderStream
        {
            GPUHandle*          res;
            String              vs;
            String              fs;
            ShaderUniforms*    uniforms;
        };
    }
}

#endif
