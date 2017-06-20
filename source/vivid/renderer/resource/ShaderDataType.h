#ifndef RENDERER_SHADER_DATA_TYPE_H
#define RENDERER_SHADER_DATA_TYPE_H

namespace vivid
{
    namespace shader_data
    {
        enum UniformType
        {
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
    }
}

#endif // RENDERER_SHADER_DATA_TYPE_H
