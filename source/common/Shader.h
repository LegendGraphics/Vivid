#ifndef COMMON_Shader_H
#define COMMON_Shader_H

#include "common/Resource.h"


namespace te
{

    class Shader : public Resource
    {
    public:
        Shader() = default;
        ~Shader() = default;

        friend class ResourceLoader;

        bool load(const String & res);
        void unload();

        // shader, texture...

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

#endif // COMMON_Shader_H
