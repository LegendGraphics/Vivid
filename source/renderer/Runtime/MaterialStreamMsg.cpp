#include "renderer/runtime/StateStream.h"


namespace te
{
    MaterialStreamMsg::MaterialStreamMsg(MsgType type, Handle handle, void* data)
        :StreamMsg(type, handle, data)
    {
    }

    MaterialStreamMsg::~MaterialStreamMsg()
    {
        /* delete static_cast<Data*>(_data);
         _data = nullptr;*/
    }

    void MaterialStreamMsg::create(RenderObject*& render_object, RenderResourceContext* rrc)
    {
        RenderMaterialObject* rmo = static_cast<RenderMaterialObject*>(render_object);
        if (!rmo) return;

        // do something if we want to update the status of rmo
        // usually get the data in the message, parse it and set the rmo accordingly
        rmo->parseStreamMsg(this);

        // create resource context
        rmo->create(rrc);

    }

    void MaterialStreamMsg::update(RenderObject*& render_object, RenderResourceContext* rrc)
    {
        RenderMaterialObject* rmo = static_cast<RenderMaterialObject*>(render_object);
        if (!rmo) return;

        // do something if we want to update the status of rmo
        // usually get the data in the message, parse it and set the rmo accordingly
        rmo->parseStreamMsg(this);

        rmo->update(rrc);
    }

    void MaterialStreamMsg::render(RenderObject*& render_object, RenderContext* rc)
    {
        RenderMaterialObject* rmo = static_cast<RenderMaterialObject*>(render_object);
        if (!rmo) return;

        // do something if we want to update the status of rmo
        // usually get the data in the message, parse it and set the rmo accordingly

        //// get model matrix
        //Data* data = static_cast<Data*>(_data);
        //rmo->setModelMat(data->model_mat);

        rmo->render(rc);
    }
}