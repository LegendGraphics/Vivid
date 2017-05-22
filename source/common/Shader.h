#ifndef COMMON_SHADER_H
#define COMMON_SHADER_H

#include "common/Resource.h"

namespace te
{
    enum class ShaderUniformType
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
    };

    template <typename T>
    struct ShaderUniform
    {
        String                      name;
        ShaderUniformType           type;
        std::vector<T>              data;
        unsigned char               size;
        int                         loc;
    };

    using ShaderUniformf = ShaderUniform<float>;
    using ShaderUniformi = ShaderUniform<int>;  // what is uniformi used for?

    using ShaderUniformfs = std::unordered_map<String, ShaderUniformf>;

    // using glsl shader
    class Shader : public Resource
    {
    public:
        using UniformTypeMap = std::unordered_map<String, ShaderUniformType>;

        static UniformTypeMap uni_type_map;

    public:
        Shader() = default;
        ~Shader() = default;

        friend class ResourceLoader;

        bool load(const String & res);
        void unload();

        // get/set uniform function needed

        String getVertexShaderContext() const { return _vs_context; }
        String getFragmentShaderContext() const { return _fs_context; }
        ShaderUniformfs getShaderUniforms() const { return _custom_uniforms; }

    protected:
        String              _vs_context;
        String              _fs_context;
        ShaderUniformfs     _custom_uniforms;
    };

    using ShaderPtr = RefPtr<Shader>;

    class ShaderManager : public ResourceManager
    {
    public:
        ShaderManager();
        ~ShaderManager();

        ResourceHandle create(const String& res);

        ShaderPtr   getShader(ResourceHandle handle);
        ShaderPtr   getShader(const String& res);
    };
}

#endif // COMMON_SHADER_H
