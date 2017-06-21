#ifndef VIVID_COMMON_MATERIAL_H
#define VIVID_COMMON_MATERIAL_H

#include "vivid/common/Resource.h"
#include "vivid/common/Shader.h"
#include "vivid/common/Texture.h"
#include "vivid/math/Vector3.h"
#include "vivid/math/Matrix.h"

namespace vivid
{
    //struct MaterialSampler
    //{
    //    ResourceHandle  texture;
    //    String          tag;    // semantic name of sampler in shader
    //};

    class Material : public Resource
    {
    public:
        Material() = default;
        ~Material() = default;

        friend class ResourceLoader;

        bool load(const String & res);
        void unload();

        ShaderPtr   getShader();
        std::vector<TexturePtr> getTextures();

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

        void setTexture(const String& name, ResourceHandle texture);

        void setShaderUniforms();
    public:
        bool hasUniform(const String& name);
        void setUniform(const String& name, const float* value, int size, shader_data::UniformType type);
        float* getUniformValue(const String& name);
        int getUniformSize(const String& name);
        shader_data::UniformType getUniformType(const String& name);

        // shader, texture...
    protected:
        // semantic name is hold in Texture already, but for fast access, use a map here
        ShaderSamplerValueMap           _samplers;
        ResourceHandle                  _shader;
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

#endif // VIVID_COMMON_MATERIAL_H
