#include "common/Material.h"
#include "common/Shader.h"
#include "io/ResourceLoader.h"
#include "io/Logger.h"

namespace te
{
    bool Material::load(const String & res)
    {
        return ResourceLoader::load(this, res);
    }

    void Material::unload()
    {

    }

    ShaderPtr  Material::getShader()
    {
        return ResourceMapper::getInstance()->get<ShaderManager>()->getShader(_shader);
    }

    float Material::getFloat(const String& name)
    {
        if (getUniformType(name) == ShaderUniformType::SCALAR)
            return *getUniformValue(name);
        else
        {
            cLog << StringUtils::format("Uniform %s is not a float", name);
            return 0;
        }
    }

    Vector3 Material::getVector3(const String& name)
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

    Matrix Material::getMatrix(const String& name)
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

    void Material::setFloat(const String& name, float value)
    {
        setUniform(name, &value, 1, ShaderUniformType::SCALAR);
    }

    void Material::setVector3(const String& name, const Vector3& value)
    {
        setUniform(name, &value.x, 3, ShaderUniformType::VECTOR3);
    }

    void Material::setMatrix(const String& name, const Matrix& value)
    {
        setUniform(name, &value(0, 0), 4 * 4, ShaderUniformType::MATRIX4X4);
    }

    bool Material::hasUniform(const String& name)
    {
        if (_uniform_map.find(name) != _uniform_map.end()) return true;
        else return false;
    }

    void Material::setUniform(const String& name, const float* value, int size, ShaderUniformType type)
    {
        if (hasUniform(name))
        {
            ShaderUniformValue& uniform = _uniform_map[name];
            uniform.type = type;
            uniform.size = size;
            uniform.data.assign(value, value + size);
        }
        else
        {
            ShaderUniformValue uniform;
            uniform.type = type;
            uniform.size = size;
            uniform.data.assign(value, value + size);
            _uniform_map.insert({ name, uniform });
        }
    }

    float* Material::getUniformValue(const String& name)
    {
        if (hasUniform(name) && _uniform_map[name].size) return &_uniform_map[name].data[0];
        else return nullptr;
    }

    int Material::getUniformSize(const String& name)
    {
        if (hasUniform(name)) return _uniform_map[name].size;
        else return 0;
    }

    ShaderUniformType Material::getUniformType(const String& name)
    {
        if (hasUniform(name)) return _uniform_map[name].type;
        else return ShaderUniformType::UNKNOWN_CLASS;
    }


    MaterialManager::MaterialManager()
        :ResourceManager(ResourceType::Material)
    {}

    MaterialManager::~MaterialManager() {}

    ResourceHandle MaterialManager::create(const String& res)
    {
        if (ResourceHandle handle = getResourceHandle(res)) return handle;
        else
        {
            MaterialPtr mat = new Material;
            if (mat->load(res))
            {
                mat->descriptor(buildDescriptor(res));
                add(mat.get());
                return getResourceHandle(res);
            }
            else return 0;
        }
    }

    MaterialPtr MaterialManager::getMaterial(ResourceHandle handle)
    {
        if (has(handle)) return dynamic_cast_ptr<Resource, Material>(getResourcePtr(handle));
        else return nullptr;
    }

    MaterialPtr MaterialManager::getMaterial(const String& res)
    {
        return getMaterial(getResourceHandle(res));
    }
}