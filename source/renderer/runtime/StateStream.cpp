#include "StateStream.h"

#include "renderer/resource/RenderMeshObject.h"

namespace te
{
    void StreamMsg::process(RenderObject *& render_object, RenderContext* rc, RenderResourceContext* rrc)
    {
        switch (_type)
        {
        case MsgType::CREATE:
            create(render_object, rrc);
            break;
        case MsgType::UPDATE:
            update(render_object, rrc);
            break;
        case MsgType::RENDER:
            render(render_object, rc);
            break;
        default: break;
        }
    }

    MeshStreamMsg::~MeshStreamMsg()
    {
        delete static_cast<Data*>(_data);
        _data = nullptr;
    }

    void MeshStreamMsg::feedData(RenderObject *& render_object)
    {
        Data* data = new Data;
        data->rmo = static_cast<RenderMeshObject*>(render_object);
        _data = (void*)data;
    }

    void MeshStreamMsg::create(RenderObject*& render_object, RenderResourceContext* rrc)
    {
        RenderMeshObject* rmo = dynamic_cast<RenderMeshObject*>(render_object);
        if (!rmo) return;

        rmo = static_cast<Data*>(_data)->rmo;
        rmo->generateGPUResource(rrc);
    }
    void MeshStreamMsg::update(RenderObject *& render_object, RenderResourceContext* rrc)
    {
    }
    void MeshStreamMsg::render(RenderObject *& render_objcet, RenderContext* rc)
    {
    }
}