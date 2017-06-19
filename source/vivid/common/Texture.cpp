#include "vivid/common/Texture.h"
#include "vivid/io/ResourceLoader.h"

namespace te
{
    bool Texture::load(const String & res)
    {
        return ResourceLoader::load(this, res);
    }

    void Texture::unload()
    {

    }

    TextureManager::TextureManager()
        :ResourceManager(ResourceType::Material)
    {}

    TextureManager::~TextureManager() {}

    ResourceHandle TextureManager::create(const String& res)
    {
        if (ResourceHandle handle = getResourceHandle(res)) return handle;
        else
        {
            TexturePtr tex = new Texture;
            if (tex->load(res))
            {
                tex->descriptor(buildDescriptor(res));
                add(tex.get());
                return getResourceHandle(res);
            }
            else return 0;
        }
    }

    TexturePtr TextureManager::getTexture(ResourceHandle handle)
    {
        if (has(handle)) return dynamic_cast_ptr<Resource, Texture>(getResourcePtr(handle));
        else return nullptr;
    }

    TexturePtr TextureManager::getTexture(const String& res)
    {
        return getTexture(getResourceHandle(res));
    }
}