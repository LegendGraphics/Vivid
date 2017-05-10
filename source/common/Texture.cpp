#include "common/Texture.h"
#include "io/ResourceLoader.h"

namespace te
{
    bool Texture::load(const String & res)
    {
        return ResourceLoader::load(this, res);
    }

    void Texture::unload()
    {

    }
}