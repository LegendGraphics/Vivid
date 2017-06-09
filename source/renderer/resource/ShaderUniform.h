#ifndef COMMON_SHADER_UNIFORM_H
#define COMMON_SHADER_UNIFORM_H

#include "base/Types.h"
#include "renderer/resource/ShaderDataType.h"

namespace te
{
    struct ShaderUniformValue
    {
        shader_data::UniformType    type;
        std::vector<float>          data;
        size_t                      size;
    };

    struct ShaderUniform
    {
        ShaderUniformValue          value;
        int                         loc;
    };

    using ShaderUniformValueMap = std::unordered_map<String, ShaderUniformValue>;

    // store run-time uniforms in shader
    class ShaderUniforms
    {
    public:
        auto& getUniforms() { return _uniforms; }

        bool hasUniform(const String& name);
        void addUniform(const String& name, shader_data::UniformType type);
        void setUniform(const String& name, const float* value, int size, shader_data::UniformType type);

    private:
        std::unordered_map<String, ShaderUniform>  _uniforms;
    };

    struct ShaderSampler
    {
        int     loc;
        int     tex_unit;
    };

    class ShaderSamplers
    {
    public:
        auto& getSamplers() { return _samplers; }

        bool hasSampler(const String& name);
        void addSampler(const String& name, int tex_unit);

    private:
        std::unordered_map<String, ShaderSampler> _samplers;
    };
}

#endif // COMMON_SHADER_UNIFORM_H