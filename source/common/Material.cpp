#include "common/Material.h"
#include "common/Shader.h"
#include "io/ResourceLoader.h"

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
        return getShader()->uniforms.getFloat(name);
    }

    Vector3 Material::getVector3(const String& name)
    {
        return getShader()->uniforms.getVector3(name);
    }

    Matrix Material::getMatrix(const String& name)
    {
        return getShader()->uniforms.getMatrix(name);
    }

    void Material::setFloat(const String& name, float value)
    {
        getShader()->uniforms.setFloat(name, value);
    }

    void Material::setVector3(const String& name, const Vector3& value)
    {
        getShader()->uniforms.setVector3(name, value);
    }

    void Material::setMatrix(const String& name, const Matrix& value)
    {
        getShader()->uniforms.setMatrix(name, value);
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