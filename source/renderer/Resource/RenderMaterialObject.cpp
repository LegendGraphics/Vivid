#include "renderer/resource/RenderMaterialObject.h"

#include "renderer/device/RenderContext.h"
#include "renderer/device/RenderDevice.h"
#include "renderer/runtime/RenderCamera.h"
#include "renderer/resource/RenderResourceContext.h"
#include "renderer/resource/ResourceStream.h"
#include "renderer/runtime/StateStream.h"

namespace te
{
    RenderObject::Type RenderMaterialObject::TYPE = RenderObject::NOT_INITIALIZED;

    RenderMaterialObject::RenderMaterialObject()
        :_material_handle(0xFFFFFFFF)
    {
    }

    RenderMaterialObject::~RenderMaterialObject()
    {
    }

    void RenderMaterialObject::create(RenderResourceContext* context)
    {
    }

    void RenderMaterialObject::update(RenderResourceContext* context)
    {
        // no gpu resource allocated 
    }

    void RenderMaterialObject::render(RenderContext* context)
    {
        setShader(context);
    }

    void RenderMaterialObject::parseStreamMsg(StreamMsg* msg)
    {
        Material* material = static_cast<Material*>(msg->getData());

        for (auto& uniform : material->getUniformValueMap())
        {
            _uniforms.setUniform(uniform.first, &uniform.second.data[0], uniform.second.size, uniform.second.type);
        }
    }

    void RenderMaterialObject::setShader(RenderContext* context)
    {
        RenderContext::ShaderCmdStream* scs = new RenderContext::ShaderCmdStream;
        scs->shader_handle = _material_handle;
        scs->uniforms = _uniforms;
        RenderContext::Command set_shader = { 0, (void*)scs, RenderContext::CommandType::BIND_SHADER_OBJECT };
        context->commands().push_back(set_shader);
    }
}

