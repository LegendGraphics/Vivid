#ifndef COMMON_TEXTURE_H
#define COMMON_TEXTURE_H

#include "common/Resource.h"


namespace te 
{

    class Texture : public Resource
    {
    public:
        Texture() = default;
        ~Texture() = default;

        friend class ResourceLoader;

        bool load(const String & res);
        void unload();

        uint32 getWidth() const { return _width; }
        uint32 getHeight() const { return _height; }
        uint32 getDepth() const { return _depth; }
        uint8* getData() const { return _img; }

        void setWidth(uint32 width) { _width = width; }
        void setHeight(uint32 height) { _height = height; }
        void setDepth(uint32 depth) { _depth = depth; }
        void setData(uint8* data) { _img = data; }
    protected:
        uint32      _width, _height, _depth;
        uint8*      _img;

    };

    using TexturePtr = RefPtr<Texture>;

    class TextureManager : public ResourceManager
    {
    public:
        TextureManager();
        ~TextureManager();

        ResourceHandle create(const String& res);

        TexturePtr   getTexture(ResourceHandle handle);
        TexturePtr   getTexture(const String& res);
    };
}

#endif // COMMON_TEXTURE_H
