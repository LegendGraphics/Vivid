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
            ShaderUniformf& uniform = _uniforms[name];
            uniform.size = size;
            uniform.data.assign(value, value + size);
        }
        else
        {
            ShaderUniformf uniform;
            uniform.loc = 0;
            uniform.name = name;
            uniform.type = type;
            uniform.size = size;
            uniform.data.assign(value, value + size);

            _uniforms.insert({ name, uniform });
        }
    }

    float* ShaderUniforms::getUniformValue(const String& name)
    {
        if (hasUniform(name) && _uniforms[name].size) return &_uniforms[name].data[0];
        else return nullptr;
    }

    int ShaderUniforms::getUniformSize(const String& name)
    {
        if (hasUniform(name)) return _uniforms[name].size;
        else return 0;
    }

    ShaderUniformType ShaderUniforms::getUniformType(const String& name)
    {
        if (hasUniform(name)) return _uniforms[name].type;
        else return ShaderUniformType::UNKNOWN_CLASS;
    }

    float ShaderUniforms::getFloat(const String& name)
    {
        if (getUniformType(name) == ShaderUniformType::SCALAR)
            return *getUniformValue(name);
        else
        {
            cLog << StringUtils::format("Uniform %s is not a float", name);
            return 0;
        }
    }

    Vector3 ShaderUniforms::getVector3(const String& name)
    {
        if (getUniformType(name) == ShaderUniformType::VECTOR3)
        {
            float* value = getUniformValue(name);
            return Vector3(value[0], value[1], value[2]);
        }
        else
        {
            cLog << StringUtils::format("Uniform %s is not a vector3", name);
            return Vector3();
        }
    }

    Matrix ShaderUniforms::getMatrix(const String& name)
    {
        if (getUniformType(name) == ShaderUniformType::MATRIX4X4)
        {
            float* value = getUniformValue(name);
            return Matrix(value[0], value[1], value[2], value[3],
                value[4], value[5], value[6], value[7], 
                value[8], value[9], value[10], value[11], 
                value[12], value[13], value[14], value[15]);
        }
        else
        {
            cLog << StringUtils::format("Uniform %s is not a Matrix", name);
            return Matrix();
        }
    }

    void ShaderUniforms::setFloat(const String& name, float value)
    {
        setUniform(name, &value, 1, ShaderUniformType::SCALAR);
    }

    void ShaderUniforms::setVector3(const String& name, const Vector3& value)
    {
        setUniform(name, &value.x, 3, ShaderUniformType::VECTOR3);
    }

    void ShaderUniforms::setMatrix(const String& name, const Matrix& value)
    {
        setUniform(name, &value(0, 0), 4*4, ShaderUniformType::MATRIX4X4);
    }
}