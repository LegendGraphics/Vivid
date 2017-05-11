#ifndef COMMON_MATERIAL_H
#define COMMON_MATERIAL_H

#include "common/Resource.h"


namespace te
{

    class Material : public Resource
    {
    public:
        Material() = default;
        ~Material() = default;

        friend class ResourceLoader;

        bool load(const String & res);
        void unload();

        // shader, texture...

    };

    using MaterialPtr = RefPtr<Material>;

    class MaterialManager : public ResourceManager
    {
    public:
        MaterialManager();
        ~MaterialManager();

        ResourceHandle create(const String& res);

        MaterialPtr   getMaterial(ResourceHandle handle);
        MaterialPtr   getMaterial(const String& res);
    };
}

#endif // COMMON_MATERIAL_H
