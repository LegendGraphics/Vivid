#ifndef COMMON_MATERIAL_H
#define COMMON_MATERIAL_H

#include "common/Resource.h"
#include "common/Shader.h"


namespace te
{
    struct MaterialSampler
    {
        ResourceHandle  texture;
        String          tag;
    };

    class Material : public Resource
    {
    public:
        Material() = default;
        ~Material() = default;

        friend class ResourceLoader;

        bool load(const String & res);
        void unload();

        ShaderPtr   getShader();

        float getFloat(const String& name);
        Vector3 getVector3(const String& name);
        Matrix getMatrix(const String& name);

        void setFloat(const String& name, float value);
        void setVector3(const String& name, const Vector3& value);
        void setMatrix(const String& name, const Matrix& value);

        // shader, texture...
    protected:
        ResourceHandle                  _shader;
        std::vector<MaterialSampler>    _samplers;
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
