#ifndef RENDERER_RESOURCE_STREAM_H
#define RENDERER_RESOURCE_STREAM_H

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
}

#endif
