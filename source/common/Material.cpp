#include "common/Material.h"
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