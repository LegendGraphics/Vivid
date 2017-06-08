#ifndef COMMON_MATERIAL_H
#define COMMON_MATERIAL_H

#include "common/Resource.h"
#include "common/Shader.h"
#include "math/Vector3.h"
#include "math/Matrix.h"

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

        void setUniform(const String& name, float a, float b, float c, float d);

        float getFloat(const String& name);
        Vector3 getVector3(const String& name);
        Matrix getMatrix(const String& name);

        void setFloat(const String& name, float value);
        void setVector2(const String& name, float a, float b);
        void setVector2(const String& name, const Vector2& value);
        void setVector3(const String& name, float a, float b, float c);
        void setVector3(const String& name, const Vector3& value);
        void setVector4(const String& name, float a, float b, float c, float d);
        void setVector4(const String& name, const Vector4& value);
        void setMatrix(const String& name, const Matrix& value);

        void setShaderUniforms();
    public:
        bool hasUniform(const String& name);
        void setUniform(const String& name, const float* value, int size, ShaderUniformType type);
        float* getUniformValue(const String& name);
        int getUniformSize(const String& name);
        ShaderUniformType getUniformType(const String& name);

        // shader, texture...
    protected:
        ResourceHandle                  _shader;
        std::vector<MaterialSampler>    _samplers;
        ShaderUniformValueMap           _uniform_map;
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
