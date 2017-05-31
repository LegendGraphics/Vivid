#include "common/ShaderUniform.h"
#include "io/Logger.h"

namespace te
{
    bool ShaderUniforms::hasUniform(const String& name)
    {
        if (_uniforms.find(name) != _uniforms.end()) return true;
        else return false;
    }

    void ShaderUniforms::setUniform(const String& name, const float* value, int size, ShaderUniformType type)
    {
        if (hasUniform(name))
        {
            ShaderUniform& uniform = _uniforms[name];
            uniform.value.type = type;
            uniform.value.size = size;
            uniform.value.data.assign(value, value + size);
        }
        else
        {
            cLog << StringUtils::format("Uniform %s doesn't exist in the shader", name);
        }
    }

    void ShaderUniforms::addUniform(const String& name)
    {
        if (!hasUniform(name))
        {
            ShaderUniform uniform;
            uniform.loc = 0;
            uniform.value.size = 0;
            uniform.value.type = ShaderUniformType::UNKNOWN_CLASS;
            _uniforms.insert({ name, uniform });
        }
        else
        {
            cLog << StringUtils::format("Uniform %s already exists in the shader", name);
        }
    }

}