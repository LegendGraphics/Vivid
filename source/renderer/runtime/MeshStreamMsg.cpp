#include "StateStream.h"

namespace te
{
    MeshStreamMsg::~MeshStreamMsg()
    {
        delete static_cast<Data*>(_data);
        _data = nullptr;
    }

    void MeshStreamMsg::create(RenderObject*& render_object, RenderResourceContext* rrc)
    {
        if (render_object)
        {
            delete static_cast<Data*>(_data)->rmo;
            return;
        }
        render_object = static_cast<Data*>(_data)->rmo; // pass the ownership to RenderWorld
    }

    void MeshStreamMsg::update(RenderObject*& render_object, RenderResourceContext* rrc)
    {
        RenderMeshObject* rmo = dynamic_cast<RenderMeshObject*>(render_object);
        if (!rmo) return;

        // do something if we want to update the status of rmo
        // usually get the data in the message, parse it and set the rmo accordingly

        rmo->update(rrc);
    }

    void MeshStreamMsg::render(RenderObject*& render_object, RenderContext* rc)
    {
        RenderMeshObject* rmo = dynamic_cast<RenderMeshObject*>(render_object);
        if (!rmo) return;

        // do something if we want to update the status of rmo
        // usually get the data in the message, parse it and set the rmo accordingly

        // get model matrix
        Data* data = static_cast<Data*>(_data);
        rmo->setModelMat(data->model_mat);

        rmo->render(rc);
    }
}