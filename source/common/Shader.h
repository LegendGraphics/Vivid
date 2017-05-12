#ifndef COMMON_SHADER_H
#define COMMON_SHADER_H

#include "common/Resource.h"

namespace te
{
    // using glsl shader
    class Shader : public Resource
    {
    public:
        Shader() = default;
        ~Shader() = default;

        friend class ResourceLoader;

        bool load(const String & res);
        void unload();

    protected:
        String      _shader_context;

    };

    using ShaderPtr = RefPtr<Shader>;

    class ShaderManager : public ResourceManager
    {
    public:
        ShaderManager();
        ~ShaderManager();

        ResourceHandle create(const String& res);

        ShaderPtr   getShader(ResourceHandle handle);
        ShaderPtr   getShader(const String& res);
    };
}

#endif // COMMON_SHADER_H
