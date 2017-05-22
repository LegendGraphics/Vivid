#include "common/Shader.h"
#include "io/ResourceLoader.h"

namespace te
{
    //Shader::Uniforms Shader::prefined_uniforms =
    //{
    //    // Predefined uniforms
    //    { "viewMat", ShaderUniformType::MATRIX4X4 },
    //    { "viewMatInv", ShaderUniformType::MATRIX4X4 },
    //    { "projMat", ShaderUniformType::MATRIX4X4 },
    //    { "viewProjMat", ShaderUniformType::MATRIX4X4 }
    //    // ...
    //};

    Shader::UniformTypeMap Shader::uni_type_map =
    {
        // Predefined types
        { "float", ShaderUniformType::SCALAR },
        { "float2", ShaderUniformType::VECTOR2 },
        { "float3", ShaderUniformType::VECTOR3 },
        { "float4", ShaderUniformType::VECTOR4 },
        { "matrix4", ShaderUniformType::MATRIX4X4 }
        // ...
    };

    bool Shader::load(const String & res)
    {
        return ResourceLoader::load(this, res);
    }

    void Shader::unload()
    {

    }

    ShaderManager::ShaderManager()
        :ResourceManager(ResourceType::Shader)
    {}

    ShaderManager::~ShaderManager() {}

    ResourceHandle ShaderManager::create(const String& res)
    {
        if (ResourceHandle handle = getResourceHandle(res)) return handle;
        else
        {
            ShaderPtr mat = new Shader;
            if (mat->load(res))
            {
                mat->descriptor(buildDescriptor(res));
                add(mat.get());
                return getResourceHandle(res);
            }
            else return 0;
        }
    }

    ShaderPtr ShaderManager::getShader(ResourceHandle handle)
    {
        if (has(handle)) return dynamic_cast_ptr<Resource, Shader>(getResourcePtr(handle));
        else return nullptr;
    }

    ShaderPtr ShaderManager::getShader(const String& res)
    {
        return getShader(getResourceHandle(res));
    }
}