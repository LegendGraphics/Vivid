#include "RenderDevice.h"

#include "RenderContext.h"
#include "../resource/RenderResourceContext.h"

namespace te
{
    RenderDevice::RenderDevice()
    {

    }

    RenderDevice::~RenderDevice()
    {
        for (RenderContext* i : _render_contexts)
        {
            delete i;
        }
        _render_contexts.erase(_render_contexts.begin(), _render_contexts.end());

        for (RenderResourceContext* i : _render_resource_contexts)
        {
            delete i;
        }
        _render_resource_contexts.erase(_render_resource_contexts.begin(), _render_resource_contexts.end());
    }

    RenderContext* RenderDevice::newContext()
    {
        _render_contexts.push_back(new RenderContext);
        return _render_contexts.back();
    }

    void RenderDevice::releaseContext(RenderContext* context)
    {
        auto it = std::find(_render_contexts.begin(), _render_contexts.end(), context);
        if (it != _render_contexts.end())
        {
            delete (*it);
        }
        _render_contexts.erase(it);
    }

    RenderResourceContext * RenderDevice::newResourceContext()
    {
        _render_resource_contexts.push_back(new RenderResourceContext);
        return _render_resource_contexts.back();
    }

    void RenderDevice::releaseResourceContext(RenderResourceContext * context)
    {
        auto it = std::find(_render_resource_contexts.begin(), _render_resource_contexts.end(), context);
        if (it != _render_resource_contexts.end())
        {
            delete (*it);
        }
        _render_resource_contexts.erase(it);
    }

    VertexDeclaration * RenderDevice::getVertexDeclarationDefinition()
    {
        return &_vertex_declaration;
    }


}