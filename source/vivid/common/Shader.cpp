#include "vivid/common/Shader.h"
#include "vivid/io/ResourceLoader.h"

namespace vivid
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
        { "float", shader_data::SCALAR },
        { "float2", shader_data::VECTOR2 },
        { "float3", shader_data::VECTOR3 },
        { "float4", shader_data::VECTOR4 },
        { "mat4", shader_data::MATRIX4X4 }
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